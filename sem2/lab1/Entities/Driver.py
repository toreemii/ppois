from Entities import Car

class Driver :
    def __init__(self, name: str, car: Car):
        self.name = name
        self.car = car
        
    def check_oil(self) -> float:
        return self.car.engine.oil