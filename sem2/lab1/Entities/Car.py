from Entities.Brakes import Brakes
from Entities.Gastank import Gastank
from Entities.Engine import Engine
from Entities.Lights import Lights
from Entities.Wheel import Wheel
from Entities.Transmission import Transmission

class Car :
    def __init__(self, gastank: Gastank, car_brand: str, brakes: Brakes, 
                 engine: Engine, lights: Lights, wheels: Wheel, 
                 transmission: Transmission):

        self.car_brand = car_brand
        self.brakes = brakes
        self.gastank = gastank
        self.engine = engine
        self.lights = lights
        self.wheels = wheels
        self.transmission = transmission
        
    def move_right(self) :
        print("Машина повернула направо.")
    
    def move_left(self) :
        print("Машина повернула налево.")
    
    def move_forward(self) :
        print("Машина поехала вперед.")
    
    def move_backward(self) :
        print("Машина поехала назад.")

    
