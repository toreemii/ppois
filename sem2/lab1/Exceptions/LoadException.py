from Exceptions.CarException import CarException

class LoadException(CarException):
    def __init__(self, message: str = "Ошибка загрузки значений."):
        super().__init__(message)