import json
from Entities.Brakes import Brakes
from Entities.Gastank import Gastank
from Entities.Engine import Engine
from Entities.Lights import Lights
from Entities.Wheel import Wheel
from Entities.Transmission import Transmission
from Entities.Car import Car
from Entities.Driver import Driver
from Entities.GasStation import GasStation
from Entities.Fuel import Fuel
from Exceptions.LoadException import LoadException

class SaveManager:
    SAVE_FILE = "car_save.json"

    @staticmethod
    def save(car: Car, driver: Driver, gasstation: GasStation):
        data = {
            "car": {
                "brand": car.car_brand,
                "brakes": car.brakes.value,
                "lights": car.lights.value,
                "wheels": car.wheels.value,
                "transmission": car.transmission.value,
                "gastank": {
                    "amount": car.gastank.amount,
                    "max_value": car.gastank.max_value
                },
                "engine": {
                    "fuel": car.engine.fuel.value,
                    "volume": car.engine.volume,
                    "power": car.engine.power,
                    "oil": car.engine.oil,
                    "launched": car.engine.launched
                }
            },
            "driver": {
                "name": driver.name
            },
            "gasstation": {
                "fuel": gasstation.fuel.value,
                "volume": gasstation.volume
            }
        }

        with open(SaveManager.SAVE_FILE, "w", encoding="utf-8") as f:
            json.dump(data, f, indent=2, ensure_ascii=False)


    @staticmethod
    def load():
        try:
            with open(SaveManager.SAVE_FILE, "r", encoding="utf-8") as f:
                data = json.load(f)
        except:
            raise LoadException()

        car_data = data["car"]
        driver_data = data["driver"]
        gs_data = data["gasstation"]

        gastank = Gastank(
            car_data["gastank"]["amount"],
            car_data["gastank"]["max_value"]
        )

        engine = Engine(
            Fuel(car_data["engine"]["fuel"]),
            car_data["engine"]["volume"],
            car_data["engine"]["power"],
            car_data["engine"]["oil"]
        )
        engine.launched = car_data["engine"]["launched"]

        car = Car(
            gastank,
            car_data["brand"],
            Brakes(car_data["brakes"]),
            engine,
            Lights(car_data["lights"]),
            Wheel(car_data["wheels"]),
            Transmission(car_data["transmission"])
        )

        driver = Driver(
            driver_data["name"],
            car
        )

        gasstation = GasStation(
            Fuel(gs_data["fuel"]),
            gs_data["volume"]
        )

        return car, driver, gasstation