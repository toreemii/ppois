# README: Система Управления Транспортной Компанией (Transport Management System)

- Классы: 64
- Поля: 215
- Уникальные поведения: 178
- Ассоциации: 42
- Исключения: 14

## Исключения (14)
Все в классе Exceptions (статические методы для throw):
- throwInvalidArgument("Недопустимый аргумент")
- throwInvalidPayment("Недопустимый метод оплаты")
- throwCapacityExceeded("Пропускная способность превышена")
- throwOrderNotFound("Заказ не найден")
- throwVehicleUnavailable("Транспорт недоступен")
- throwClientNotFound("Клиент не найден")
- throwDriverNotFound("Водитель не найден")
- throwRouteNotFound("Маршрут не найден")
- throwHubFull("Хаб переполнен")
- throwPaymentFailed("Оплата не удалась")
- throwInvalidCard("Некорректная карта")
- throwInsufficientFunds("Недостаточно средств")
- throwDuplicateOrder("Дубликат заказа")
- throwInvalidWeight("Недопустимый вес груза")

## Классы
Формат: Класс Поля Методы → Ассоциации (классы как поля/параметры)

Client 15 20 → IClient, Order, PaymentManager, ClientActivityLogger, LoyaltyManager
- Поля: clientId, name, address, phoneNumber, email, orders, discountRate, loyaltyPoints, lastOrderDate, preferredPaymentMethod, clientType, emergencyContact, paymentManager, activityLogger, loyaltyManager
- Методы: getClientId, getName, getAddress, getPhoneNumber, getEmail, setEmail, setPhoneNumber, updateContactInfo, getOrders, placeOrder, getDiscountRate, setDiscountRate, getLoyaltyPoints, getLastOrderDate, makePayment, makeOrder, logClientActivity, applyLoyaltyDiscount, checkEligibilityForPriority

Order 9 14 → IOrder, Passenger, PaymentMethod, Vehicle, Client, Driver
- Поля: orderId, passengers, paymentType, cargoWeight, vehicle, driver, customer, status, totalCost
- Методы: getOrderId, getPassengers, getPaymentType, getCargoWeight, getVehicle, getStatus, setStatus, calculateCost, getTotalCost, createOrder, getCustomer, assignVehicleAndEmployee, setTotalCost, getDriver

Passenger 3 3
- Поля: name, weight, destination
- Методы: getName, getWeight, getDestination

PaymentMethod 0 2 → CardPayment, CashPayment
- Методы: processPayment, getType

CardPayment 1 2 → PaymentMethod
- Поля: cardNumber
- Методы: processPayment, getType

CashPayment 0 2 → PaymentMethod
- Методы: processPayment, getType

Vehicle 7 7 → Fuel, VehicleStatus, Driver
- Поля: vehicleId, fuel, fuelConsumptionRate, currentFuelLevel, maxLoadCapacity, status, currentCargo, currentPeople
- Методы: refuel, assignDriver, getVehicleId, getStatus, getMaxLoad, isAvailable, calculateFuelConsumption

Fuel 1 1
- Поля: fuelType
- Методы: getType

VehicleStatus 1 1
- Поля: isOperational
- Методы: isAvailable

Driver 5 5 → Employee, Reportable
- Поля: employeeId, firstName, lastName, drivingExperience, preferredVehicleType, licenseType
- Методы: submitTripReport, getLicenseType, setLicenseType, getEmployeeId, getFirstName

Captain 3 2 → Employee, Reportable
- Поля: employeeId, firstName, lastName
- Методы: submitTripReport

Conductor 3 2 → Employee, Reportable
- Поля: employeeId, firstName, lastName
- Методы: submitTripReport

Employee 3 3
- Поля: employeeId, firstName, lastName
- Методы: getEmployeeId, getFirstName, getLastName

TransportCompany 6 8 → Depot, IClient, IOrder, Analytics, Logistics, AuditManager
- Поля: companyName, depots, clients, orders, analytics, logistics, lastAuditDate
- Методы: addClient, addOrder, addDepot, getClients, getOrders, getCompanyName, generateReport, computeRevenue

Logistics 6 8 → IOrder, IVehicle, Manager, RouteOptimizer, RoutePlanner, ManagerCoordinator
- Поля: orders, vehicles, managers, optimizer, routePlanner, managerCoordinator
- Методы: getOrders, addOrder, addVehicle, addManager, checkAvailability, planRoute, optimizeRoute, getAvailableVehicles

Analytics 2 6 → Order, Vehicle
- Поля: totalFuelConsumption, analyzedOrders
- Методы: generateReport, analyzedOrderCompletion, getTotalFuelConsumption, addOrder, calculateFuelEfficiency, getTotalRevenue

Depot 3 4 → Vehicle
- Поля: depotId, location, vehicles
- Методы: addVehicle, getDepotId, getLocation, getAvailableVehicles

RouteOptimizer 0 1 → Order
- Методы: optimizeRoute

RoutePlanner 0 1 → Order
- Методы: planRoute

ManagerCoordinator 0 1 → Manager
- Методы: coordinateManagers

Hub 3 5 → Shipment, Route
- Поля: hubId, capacity, incoming
- Методы: getHubId, transShip, sortByDestination, checkCapacity, getCurrentLoad

Route 1 1
- Поля: routeId
- Методы: getRouteId

Shipment 2 2
- Поля: shipmentId, weight
- Методы: getShipmentId, getWeight

RevenueCalculator 0 1 → TransportCompany
- Методы: computeRevenue

PaymentManager 0 3 → PaymentMethod
- Методы: makePayment, makeOrderPayment, validatePayment

ClientActivityLogger 0 1 → Client
- Методы: logClientActivity

LoyaltyManager 0 3 → Client
- Методы: applyLoyaltyDiscount, checkEligibilityForPriority, addLoyaltyPoints

Manager 5 6 → Employee, License
- Поля: employeeId, name, position, salary, license
- Методы: getEmployeeId, getName, getPosition, getSalary, getLicense, assignTask

License 1 1
- Поля: licenseType
- Методы: getType

Invoice 4 3 → Order, PaymentMethod
- Поля: invoiceId, order, paymentMethod, amount
- Методы: generateInvoice, sendInvoice, getInvoiceId

GPSDevice 3 3
- Поля: deviceId, latitude, longitude
- Методы: updateLocation, getCoordinates, isOnline

Sensor 2 2
- Поля: sensorType, value
- Методы: readValue, calibrate

Printer 3 3
- Поля: printerId, isOnline, paperLevel
- Методы: printLabel, checkStatus, refillPaper

Scanner 2 2
- Поля: scannerId, isConnected
- Методы: scanBarcode, getLastScan

Camera 3 3
- Поля: cameraId, location, isRecording
- Методы: startRecording, stopRecording, saveClip

AuditLog 1 2
- Поля: logEntries
- Методы: addEntry, exportLog

BackupSystem 2 2
- Поля: lastBackup, storagePath
- Методы: createBackup, restoreBackup

NotificationService 1 2 → Client
- Поля: notificationQueue
- Методы: sendSMS, sendEmail

ReportGenerator 2 2
- Поля: reportType, data
- Методы: generatePDF, exportCSV

SecuritySystem 2 2
- Поля: isArmed, lastEvent
- Методы: arm, disarm

TemperatureSensor 2 2
- Поля: currentTemp, threshold
- Методы: checkTemperature, alertIfHot

WeightSensor 2 2
- Поля: currentWeight, maxWeight
- Методы: measureWeight, checkOverload

BarcodeGenerator 1 2
- Поля: prefix
- Методы: generateCode, validateCode

ConfigManager 3 3
- Поля: configFile, settings, version
- Методы: loadConfig, saveConfig, getSetting

DatabaseConnector 2 2
- Поля: connectionString, isConnected
- Методы: connect, executeQuery

APIClient 2 2
- Поля: apiKey, endpoint
- Методы: sendRequest, parseResponse

CacheManager 2 2
- Поля: cacheSize, entries
- Методы: getCached, invalidateCache

ThreadPool 2 2
- Поля: workerCount, taskQueue
- Методы: submitTask, shutdown

CircuitBreaker 2 2
- Поля: failureCount, state
- Методы: allowRequest, recordFailure

RateLimiter 2 2
- Поля: requestsPerSecond, bucket
- Методы: allowRequest, refill

EventBus 1 2
- Поля: subscribers
- Методы: publishEvent, subscribe

Car 0 5 → Vehicle
- Методы: loadCargo, unloadCargo, loadPeople, unloadPeople, calculateFuelConsumption

Bus 0 5 → Vehicle
- Методы: loadCargo, unloadCargo, loadPeople, unloadPeople, calculateFuelConsumption

Truck 0 5 → Vehicle
- Методы: loadCargo, unloadCargo, loadPeople, unloadPeople, calculateFuelConsumption

Train 0 5 → Vehicle
- Методы: loadCargo, unloadCargo, loadPeople, unloadPeople, calculateFuelConsumption

Ship 0 5 → Vehicle
- Методы: loadCargo, unloadCargo, loadPeople, unloadPeople, calculateFuelConsumption

Airplane 0 5 → Vehicle
- Методы: loadCargo, unloadCargo, loadPeople, unloadPeople, calculateFuelConsumption

Van 0 5 → Vehicle
- Методы: loadCargo, unloadCargo, loadPeople, unloadPeople, calculateFuelConsumption

Freight 3 3
- Поля: freightId, weight, isHazardous
- Методы: getFreightId, getWeight, isHazardous

CargoInspector 1 3
- Поля: inspectorId
- Методы: inspectCargo, getInspectorId

Complaint 0 1
- Методы: textComplaint

Billing 1 3 → Invoice, Client
- Поля: billingId
- Методы: getBillingId, processInvoice

AuditManager 0 1 → TransportCompany
- Методы: auditOperations

IClient 0 13
- Методы: getClientId, getName, getAddress, getPhoneNumber, getEmail, setEmail, setPhoneNumber, updateContactInfo, getOrders, placeOrder, getDiscountRate, getLoyaltyPoints, getLastOrderDate

IOrder 0 12
- Методы: getOrderId, getPassengers, getPaymentType, getCargoWeight, getVehicle, getStatus, setStatus, calculateCost, getTotalCost, createOrder, getCustomer, assignVehicleAndEmployee

IVehicle 0 7
- Методы: refuel, assignDriver, getVehicleId, getStatus, getMaxLoad, isAvailable, calculateFuelConsumption

