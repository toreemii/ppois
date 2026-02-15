import unittest
from unittest.mock import patch, Mock
import os
import json
from datetime import datetime

from Entities.Brakes import Brakes
from Entities.Car import Car
from Entities.Driver import Driver
from Entities.Engine import Engine
from Entities.Fuel import Fuel
from Entities.GasStation import GasStation
from Entities.Gastank import Gastank
from Entities.Lights import Lights
from Entities.Station import Station
from Entities.Transmission import Transmission
from Entities.Wheel import Wheel
from Exceptions.CarException import CarException
from Exceptions.DeficitException import DeficitException
from Exceptions.DifferentFuelException import DifferentFuelException
from Exceptions.FuelException import FuelException
from Utility.Menu import Menu
from Utility.SaveManager import SaveManager


class TestBrakesFuelLightsTransmissionWheel(unittest.TestCase):
    def test_all_enums_have_correct_values(self):
        self.assertEqual(Brakes.disc_brakes.value, "disc_brakes")
        self.assertEqual(Brakes.drum_brakes.value, "drum_brakes")
        self.assertEqual(Brakes.handbrake.value, "handbrake")

        self.assertEqual(Fuel.type_92.value, "92")
        self.assertEqual(Fuel.diesel.value, "diesel")

        self.assertEqual(Lights.head_lights.value, "head_lights")

        self.assertEqual(Transmission.manual.value, "manual")
        self.assertEqual(Transmission.continuously_variable.value, "continuously_variable")

        self.assertEqual(Wheel.all_season_tires.value, "all_season_tires")


class TestEngine(unittest.TestCase):
    def setUp(self):
        self.engine = Engine(Fuel.type_95, 1.6, 122, 4.2)

    def test_initial_state(self):
        self.assertFalse(self.engine.launched)
        self.assertEqual(self.engine.fuel, Fuel.type_95)
        self.assertEqual(self.engine.volume, 1.6)
        self.assertEqual(self.engine.power, 122)
        self.assertEqual(self.engine.oil, 4.2)

    def test_start_and_stop(self):
        self.engine.start_engine()
        self.assertTrue(self.engine.launched)
        self.engine.end_engine()
        self.assertFalse(self.engine.launched)

    def test_get_launched(self):
        self.assertFalse(self.engine.get_launched())
        self.engine.start_engine()
        self.assertTrue(self.engine.get_launched())


class TestGastank(unittest.TestCase):
    def test_get_amount_returns_current_value(self):
        tank = Gastank(17.3, 55.0)
        self.assertEqual(tank.get_amount(), 17.3)

    def test_attributes_are_stored_correctly(self):
        tank = Gastank(0.0, 40.0)
        self.assertEqual(tank.amount, 0.0)
        self.assertEqual(tank.max_value, 40.0)


class TestGasStation(unittest.TestCase):
    def setUp(self):
        self.tank = Gastank(12.5, 60.0)
        self.engine = Engine(Fuel.type_92, 2.0, 150, 5.5)
        self.car = Car(
            self.tank, "Toyota", Brakes.disc_brakes, self.engine,
            Lights.head_lights, Wheel.all_season_tires, Transmission.automatic
        )
        self.station = GasStation(Fuel.type_92, 300.0)

    def test_successful_refuel_normal_case(self):
        self.station.fill_fuel(self.car, 25.0)
        self.assertAlmostEqual(self.car.gastank.amount, 37.5)
        self.assertAlmostEqual(self.station.volume, 275.0)

    def test_refuel_to_exact_max(self):
        self.car.gastank.amount = 58.0
        self.station.fill_fuel(self.car, 2.0)
        self.assertEqual(self.car.gastank.amount, 60.0)

    def test_refuel_zero_liters_allowed(self):
        before = self.car.gastank.amount
        self.station.fill_fuel(self.car, 0.0)
        self.assertEqual(self.car.gastank.amount, before)

    def test_refuel_negative_amount_raises_exception(self):
        with self.assertRaises(FuelException):  # или можно ввести свою проверку
            self.station.fill_fuel(self.car, -5.0)

    def test_different_fuel_type_raises_exception(self):
        self.engine.fuel = Fuel.type_95
        with self.assertRaises(DifferentFuelException):
            self.station.fill_fuel(self.car, 10.0)

    def test_overfill_raises_FuelException(self):
        with self.assertRaises(FuelException):
            self.station.fill_fuel(self.car, 60.0)  # 12.5 + 60 > 60

    def test_station_out_of_fuel_raises_DeficitException(self):
        empty_station = GasStation(Fuel.type_92, 3.0)
        with self.assertRaises(DeficitException):
            empty_station.fill_fuel(self.car, 10.0)


class TestCar(unittest.TestCase):
    def setUp(self):
        tank = Gastank(20.0, 50.0)
        engine = Engine(Fuel.type_95, 2.5, 200, 6.0)
        self.car = Car(
            tank, "BMW", Brakes.disc_brakes, engine,
            Lights.head_lights, Wheel.summer_tires, Transmission.automatic
        )

    @patch('builtins.print')
    def test_movement_methods_print_correct_messages(self, mock_print):
        self.car.move_forward()
        mock_print.assert_called_with("Машина поехала вперед.")

        self.car.move_backward()
        mock_print.assert_called_with("Машина поехала назад.")


class TestSaveManager(unittest.TestCase):
    def setUp(self):
        self.tank = Gastank(8.7, 55.0)
        self.engine = Engine(Fuel.type_98, 3.0, 354, 7.8)
        self.engine.launched = True
        self.car = Car(
            self.tank, "Audi", Brakes.drum_brakes, self.engine,
            Lights.head_lights, Wheel.winter_tires, Transmission.manual
        )
        self.driver = Driver("Алексей", self.car)
        self.station = GasStation(Fuel.type_98, 180.5)
        self.save_path = "test_save_temp.json"
        SaveManager.SAVE_FILE = self.save_path  # временно переопределяем

    def tearDown(self):
        if os.path.exists(self.save_path):
            os.remove(self.save_path)

    def test_save_creates_valid_json(self):
        SaveManager.save(self.car, self.driver, self.station)
        self.assertTrue(os.path.exists(self.save_path))

        with open(self.save_path, encoding="utf-8") as f:
            data = json.load(f)

        self.assertIn("car", data)
        self.assertEqual(data["car"]["brand"], "Audi")
        self.assertEqual(data["car"]["engine"]["launched"], True)
        self.assertEqual(data["driver"]["name"], "Алексей")
        self.assertAlmostEqual(data["gasstation"]["volume"], 180.5)

    def test_load_restores_state_correctly(self):
        SaveManager.save(self.car, self.driver, self.station)
        loaded_car, loaded_driver, loaded_station = SaveManager.load()

        self.assertEqual(loaded_car.car_brand, "Audi")
        self.assertEqual(loaded_car.brakes, Brakes.drum_brakes)
        self.assertTrue(loaded_car.engine.launched)
        self.assertAlmostEqual(loaded_car.gastank.amount, 8.7)
        self.assertEqual(loaded_driver.name, "Алексей")
        self.assertAlmostEqual(loaded_station.volume, 180.5)

    def test_load_non_existing_file_returns_default_state(self):
        if os.path.exists(self.save_path):
            os.remove(self.save_path)

        car, driver, station = SaveManager.load()

        self.assertEqual(car.car_brand, "Lada")
        self.assertEqual(driver.name, "Водитель по умолчанию")
        self.assertEqual(station.volume, 1000.0)

    @patch("json.load")
    def test_load_corrupted_json_falls_back_to_default(self, mock_json_load):
        mock_json_load.side_effect = json.JSONDecodeError("fake", "doc", 0)

        with patch("builtins.open", create=True):
            car, driver, station = SaveManager.load()

        self.assertEqual(car.car_brand, "Lada")  # дефолт


class TestExceptionsMessages(unittest.TestCase):
    def test_exception_messages(self):
        self.assertEqual(str(DifferentFuelException()), "Разное топливо.")
        self.assertEqual(str(FuelException()), "Переполнение бака.")
        self.assertEqual(str(DeficitException()), "Дефицит топлива.")


if __name__ == '__main__':
    unittest.main()