
from core.Entities import Car, Driver, GasStation, Gastank, Engine, Fuel, Brakes, Lights, Wheel, Transmission
from core.Utility import SaveManager
class CarService:
    def __init__(self):
        self.last_message = "Система готова к работе"
        try:
            self.car, self.driver, self.gas_station = SaveManager.SaveManager.load()
        except Exception as e:
            print(f"Загрузка не удалась, создаю новую машину. Ошибка: {e}")

            gastank = Gastank.Gastank(amount=20.0, max_value=60.0)
            engine = Engine.Engine(fuel=Fuel.Fuel.type_95, volume=2.0, power=150, oil=5.0)

            self.car = Car.Car(
                gastank=gastank,
                car_brand="Tesla Simulator",
                brakes=Brakes.Brakes.disc_brakes,
                engine=engine,
                lights=Lights.Lights.head_lights,
                wheels=Wheel.Wheel.summer_tires,
                transmission=Transmission.Transmission.automatic
            )

            self.driver = Driver.Driver(name="Иннокентий", car=self.car)
            self.gas_station = GasStation.GasStation(fuel=Fuel.Fuel.type_95, volume=1000.0)

    def start_engine(self):
        self.car.engine.start_engine()
        return "Двигатель запущен"
    
    def drive(self, direction: str):
        if not self.car.engine.launched:
            self.last_message = "Ошибка: Сначала запустите двигатель!"
            return

        if direction == "forward":
            self.car.move_forward()
            self.last_message = "Машина поехала вперед"
        elif direction == "back":
            self.car.move_backward()
            self.last_message = "Машина поехала назад"
        elif direction == "left":
            self.car.move_left()
            self.last_message = "Поворот налево"
        elif direction == "right":
            self.car.move_right()
            self.last_message = "Поворот направо"

    def get_status(self):
        return {
            "brand": self.car.car_brand,
            "fuel": self.car.gastank.amount,
            "engine_on": self.car.engine.launched,
            "driver": self.driver.name,
            "message": self.last_message 
        }
    def refuel(self, amount: float):
        try:
            if amount > 0:
                self.gas_station.fill_fuel(self.car, amount)
                self.last_message = f"Заправлено {amount} л. В баке теперь {self.car.gastank.amount} л."
            else:
                self.last_message = "Ошибка заправки: отрицательное топливо"
        except Exception as e:
            self.last_message = f"Ошибка заправки: {str(e)}"

    def check_oil(self):
        oil_level = self.driver.check_oil()
        self.last_message = f"Уровень масла: {oil_level}"

    def maintenance(self):
        from core.Entities import Station 
        station = Station()
        station.maintenance()
        self.last_message = "Техническое обслуживание пройдено успешно!"

    def change_driver(self, name: str):
        self.driver.name = name
        self.last_message = f"Водитель сменен на: {name}"

    def stop_engine(self):
        self.car.engine.end_engine()
        self.last_message = "Двигатель заглушен"