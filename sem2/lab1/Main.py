from Entities.Car import Car
from Entities.Driver import Driver
from Entities.Engine import Engine
from Entities.GasStation import GasStation
from Entities.Gastank import Gastank
from Entities.Station import Station
from Entities.Fuel import Fuel
from Utility.Menu import Menu
from Entities.Brakes import Brakes
from Entities.Lights import Lights
from Entities.Wheel import Wheel
from Entities.Transmission import Transmission
from Exceptions.DifferentFuelException import DifferentFuelException
from Exceptions.FuelException import FuelException
from Exceptions.DeficitException import DeficitException
from Exceptions.LoadException import LoadException
from Utility.SaveManager import SaveManager


try:
    car, driver, gasstation = SaveManager.load()
except LoadException as e:
    gastank: GasStation = Gastank(15.6, 60.0)
    gasstation: GasStation = GasStation(Fuel.type_92, 30.0)
    fuel: Fuel = Fuel.type_92
    car_brand: str = "Mercedes"
    brakes: Brakes = Brakes.drum_brakes
    engine: Engine = Engine(fuel, 3.0, 600, 8.0)
    station: Station = Station()

    car: Car = Car(gastank, car_brand, brakes, engine, Lights.head_lights,
           Wheel.all_season_tires, Transmission.continuously_variable)

    driver: Driver = Driver("Иннокентий", car)
    print(e)

while True:
    Menu.main_menu()
    choice: str = input("Выберите номер: ")
    match choice:
        case "1":
            car.engine.start_engine() 
            print("Двигатель запущен.")
        case "2":
            if not car.engine.get_launched():
                print("Заведите двигатель.")
                continue
            Menu.drive_menu()
            choiceDrive: str = input("Выберите номер: ")
            match choiceDrive:
                case "1":
                    car.move_right()
                case "2":
                    car.move_left()
                case "3":
                    car.move_forward()
                case "4":
                    car.move_backward()
                case _:
                    print("Неправильный ввод. Попробуйте ещё раз.")
        case "3": 
            Menu.refuel_question()
            liters: float = float(input())
            try:
                gasstation.fill_fuel(car, liters)
                print(f"Уровень топлива: {car.gastank.get_amount()}")
            except FuelException as e:
                print(e)
            except DifferentFuelException as e:
                print(e)
            except DeficitException as e:
                print(e)
        case "4":
            oil: int = driver.check_oil()
            print(f"Уровень  масла {oil}")
        case "5":
            station.maintenance()
        case "6":
            Menu.driver_menu()
            choiceDriver: str = input("Выберите номер: ")
            match choiceDriver:
                case "1":
                    driver: Driver = Driver("Иннокентий", car)
                    print("Выбран водитель Иннокентий.")
                case "2":
                    driver: Driver = Driver("Гоша", car)
                    print("Выбран водитель Гоша.")
                case "3":
                    driver: Driver = Driver("Борис", car)
                    print("Выбран водитель Борис.")
                case _:
                    print("Неправильный ввод. Попробуйте ещё раз.")
        case "7":
            car.engine.end_engine()
            print("Двигатель заглушен.")
        case "8":
            SaveManager.save(car, driver, gasstation)
            break
        case _:
            print("Неправильный ввод. Попробуйте ещё раз.")