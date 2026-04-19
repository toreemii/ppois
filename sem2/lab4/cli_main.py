from core.service import CarService
from core.Utility import Menu

def main():
    service = CarService()
    print("--- Запущена консольная версия управления (ЛР4) ---")

    while True:
        Menu.Menu.main_menu()
        choice = input("Выберите пункт: ")

        if choice == "1":
            print(service.start_engine())
        elif choice == "2":
            direction = input("Куда едем? (forward/back/left/right): ")
            service.drive(direction)
            print(service.last_message)
        elif choice == "3":
            amount = float(input("Сколько литров?: "))
            service.refuel(amount)
            print(service.last_message)
        elif choice == "4":
            service.check_oil()
            print(service.last_message)
        elif choice == "8":
            from core.Entities import SaveManager
            SaveManager.save(service.car, service.driver, service.gas_station)
            print("Сохранено. Выход...")
            break

if __name__ == "__main__":
    main()