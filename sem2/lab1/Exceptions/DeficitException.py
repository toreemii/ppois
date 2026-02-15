from Exceptions.CarException import CarException

class DeficitException(CarException):
    def __init__(self, message: str = "Дефицит топлива."):
        super().__init__(message)