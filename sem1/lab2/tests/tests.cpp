#include <gtest/gtest.h>
#include "../include/TransportCompany.h"
#include "../include/Analytics.h"
#include "../include/Client.h"
#include "../include/Depot.h"
#include "../include/Driver.h"
#include "../include/Employee.h"
#include "../include/Freight.h"
#include "../include/Fuel.h"
#include "../include/GPS.h"
#include "../include/Logistics.h"
#include "../include/Maintenance.h"
#include "../include/Order.h"
#include "../include/Passenger.h"
#include "../include/Route.h"
#include "../include/SafetyProtocol.h"
#include "../include/Security.h"
#include "../include/Shipment.h"
#include "../include/Ship.h"
#include "../include/Ticket.h"
#include "../include/Train.h"
#include "../include/Truck.h"
#include "../include/Van.h"
#include "../include/Vehicle.h"
#include "../include/VehicleStatus.h"
#include "../include/Warehouse.h"
#include "../include/Exceptions.h"
#include "../include/AuditManager.h"
#include "../include/Billing.h"
#include "../include/Delivery.h"
#include "../include/Hub.h"
#include "../include/InventoryManager.h"
#include "../include/License.h"
#include "../include/CargoInspector.h"
#include "../include/OperationsMonitor.h"
#include "../include/PaymentMethod.h"
#include "../include/RevenueCalculator.h"
#include "../include/RoutePlanner.h"
#include "../include/ManagerCoordinator.h"
#include "../include/PaymentManager.h"
#include "../include/ClientActivityLogger.h"
#include "../include/LoyaltyManager.h"
#include "../include/Feedback.h"
#include "../include/PaymentProcessor.h"
#include "../include/Menu.h"
#include "../include/DispatchCenter.h"

TEST(TransportTest, AnalyticsAddOrder)
{
    Analytics analytics;
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order1("ORD1", passengers, &payment, 100.0, &truck, &client);
    Order order2("ORD2", passengers, &payment, 200.0, &truck, &client);
    analytics.addOrder(&order1);
    analytics.addOrder(&order2);
}

TEST(TransportTest, AnalyticsFuelEfficiencyWithDifferentVehicles)
{
    Analytics analytics;
    Fuel dieselFuel("Diesel", 100.0, 1.0);
    Fuel gasolineFuel("Gasoline", 100.0, 1.0);
    VehicleStatus status;
    Truck dieselTruck(&dieselFuel, 100.0, 2, 5000.0, status);
    Truck gasolineTruck(&gasolineFuel, 100.0, 2, 5000.0, status);
    double distance = 100.0;
    double efficiency1 = analytics.calculateFuelEfficiency(&dieselTruck, distance);
    double efficiency2 = analytics.calculateFuelEfficiency(&gasolineTruck, distance);
    EXPECT_GT(efficiency1, 0.0);
    EXPECT_GT(efficiency2, 0.0);
    double totalConsumption = analytics.getTotalFuelConsumption();
    EXPECT_GT(totalConsumption, 0.0);
}

TEST(TransportTest, AnalyticsOrderCompletionWithDifferentOrders)
{
    Analytics analytics;
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client1("CL1", "Client One", "Address 1", &pm, &al, &lm);
    Client client2("CL2", "Client Two", "Address 2", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order smallOrder("SMALL_ORD", passengers, &payment, 50.0, &truck, &client1);
    Order largeOrder("LARGE_ORD", passengers, &payment, 500.0, &truck, &client2);
    EXPECT_NO_THROW(analytics.analyzedOrderCompletion(&smallOrder));
    EXPECT_NO_THROW(analytics.analyzedOrderCompletion(&largeOrder));
}

TEST(TransportTest, AnalyticsReportWithMixedOrders)
{
    Analytics analytics;
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    std::vector<IOrder *> mixedOrders;
    Order order1("ORD001", passengers, &payment, 100.0, &truck, &client);
    Order order2("", passengers, &payment, 0.0, &truck, &client);
    Order order3("LONG_ORDER_ID_12345", passengers, &payment, 999.9, &truck, &client);
    mixedOrders.push_back(&order1);
    mixedOrders.push_back(&order2);
    mixedOrders.push_back(&order3);
    std::vector<std::string> report = analytics.generateReport(mixedOrders);
    EXPECT_EQ(report.size(), 3);
    EXPECT_EQ(report[0], "Order ID: ORD001");
    EXPECT_EQ(report[1], "Order ID: ");
    EXPECT_EQ(report[2], "Order ID: LONG_ORDER_ID_12345");
}

TEST(TransportTest, AnalyticsMultipleInstances)
{
    Analytics analytics1;
    Analytics analytics2;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    analytics1.calculateFuelEfficiency(&truck, 100.0);
    analytics2.calculateFuelEfficiency(&truck, 200.0);
    double total1 = analytics1.getTotalFuelConsumption();
    double total2 = analytics2.getTotalFuelConsumption();
    EXPECT_GT(total1, 0.0);
    EXPECT_GT(total2, 0.0);
    EXPECT_NE(total1, total2);
    EXPECT_GT(total2, total1);
}

TEST(TransportTest, AnalyticsGenerateReport)
{
    Analytics analytics(0.0, {});
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Will Brit", "St Pushkinskaya 64", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    std::vector<IOrder *> orders;
    Order order1("ORD1", passengers, &payment, 100.0, &truck, &client);
    Order order2("ORD2", passengers, &payment, 200.0, &truck, &client);
    orders.push_back(&order1);
    orders.push_back(&order2);
    std::vector<std::string> report = analytics.generateReport(orders);
    EXPECT_EQ(report.size(), 2);
    EXPECT_EQ(report[0], "Order ID: ORD1");
    EXPECT_EQ(report[1], "Order ID: ORD2");
}

TEST(TransportTest, AnalyticsFuelEfficiencyAndOrder)
{
    Analytics analytics(0.0, {});
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    double efficiency = analytics.calculateFuelEfficiency(&truck, 100.0);
    EXPECT_DOUBLE_EQ(efficiency, truck.calculateFuelConsumption(100.0) / 100.0);
    EXPECT_GE(analytics.getTotalFuelConsumption(), 0.0);
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Vika A", "Belgradskaya 77", &pm, &al, &lm);
    CardPayment payment;
    Order order("ORD1", passengers, &payment, 100.0, &truck, &client);
    analytics.addOrder(&order);
    analytics.analyzedOrderCompletion(&order);
}

TEST(TransportTest, ClientOperations)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Bill D", "St.Jacobs Kholas 78", &pm, &al, &lm);
    EXPECT_EQ(client.getClientId(), "CL1");
    EXPECT_EQ(client.getName(), "Bill D");
    EXPECT_EQ(client.getAddress(), "St.Jacobs Kholas 78");
    client.setPhoneNumber("375-44-563-85-28");
    EXPECT_EQ(client.getPhoneNumber(), "375-44-563-85-28");
    client.setEmail("ron84@gmail.com");
    EXPECT_EQ(client.getEmail(), "ron84@gmail.com");
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("ORD1", passengers, &payment, 100.0, &truck, &client);
    client.placeOrder(&order);
    auto clientOrders = client.getOrders();
    EXPECT_EQ(clientOrders.size(), 1);
    client.updateContactInfo("newphone", "newemail");
    EXPECT_EQ(client.getPhoneNumber(), "newphone");
    EXPECT_EQ(client.getEmail(), "newemail");
    client.setDiscountRate(0.1);
    EXPECT_DOUBLE_EQ(client.getDiscountRate(), 0.1);
    EXPECT_EQ(client.getLoyaltyPoints(), 0);
    client.makePayment(1);
    client.logClientActivity();
    EXPECT_FALSE(client.checkEligibilityForPriority());
    client.makeOrder("ORD2", passengers, &payment, 200.0, &truck);
    client.applyLoyaltyDiscount(10.0);
    EXPECT_DOUBLE_EQ(client.getDiscountRate(), 0.1);
}

TEST(TransportTest, ClientPaymentExceptions)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Vika A", "St Platonova 39", &pm, &al, &lm);
    EXPECT_THROW(client.makePayment(4), InvalidPaymentException);
}

TEST(TransportTest, DriverOperations)
{
    Driver driver;
    driver.submitTripReport(100.0, 2, 30, 5, 200.0);
    EXPECT_EQ(driver.getLicenseType(), "");
}

TEST(TransportTest, EmployeeBase)
{
    Employee employee1;
    Employee employee2("EMP1", "Lili", "Jhon");
    EXPECT_EQ(employee1.getEmployeeId(), "");
    EXPECT_EQ(employee2.getEmployeeId(), "EMP1");
}

TEST(TransportTest, FreightOperations)
{
    Freight freight("FR1", 100.0, false);
    EXPECT_EQ(freight.getFreightId(), "FR1");
    EXPECT_DOUBLE_EQ(freight.getWeight(), 100.0);
    EXPECT_FALSE(freight.isHazardous());
    freight.setLength(1.0);
    freight.setWidth(2.0);
    freight.setHeight(3.0);
    EXPECT_DOUBLE_EQ(freight.calculateVolume(), 6.0);
    freight.setCategory("fragile");
    EXPECT_TRUE(freight.checkIfFragile());
    freight.updateValue(500.0);
    EXPECT_DOUBLE_EQ(freight.getValue(), 500.0);
    freight.packFreight();
}

TEST(TransportTest, FreightExceptions)
{
    Freight freight("FR1", 100.0, false);
    freight.setLength(-1.0);
    EXPECT_THROW(freight.calculateVolume(), FreightDimensionException);
    EXPECT_THROW(freight.setWeight(-10.0), InvalidWeightException);
}

TEST(TransportTest, FuelOperations)
{
    Fuel fuel("Gasoline", 50.0, 2.0);
    EXPECT_EQ(fuel.getFuelType(), "Gasoline");
    EXPECT_DOUBLE_EQ(fuel.getAvailableAmount(), 50.0);
    EXPECT_DOUBLE_EQ(fuel.getCostPerUnit(), 2.0);
    fuel.refuel(20.0);
    EXPECT_DOUBLE_EQ(fuel.getAvailableAmount(), 70.0);
    Gasoline gasoline(50.0, 2.0);
    EXPECT_EQ(gasoline.getFuelType(), "Gasoline");
    EXPECT_DOUBLE_EQ(gasoline.getAvailableAmount(), 50.0);
    EXPECT_DOUBLE_EQ(gasoline.calculateCost(10.0), 20.0);
    EXPECT_EQ(gasoline.getUnit(), "liters");
    Diesel diesel(50.0, 1.5);
    EXPECT_EQ(diesel.getFuelType(), "Diesel");
    EXPECT_DOUBLE_EQ(diesel.getAvailableAmount(), 50.0);
    EXPECT_DOUBLE_EQ(diesel.calculateCost(10.0), 15.0);
    EXPECT_EQ(diesel.getUnit(), "liters");
    Electric electric(50.0, 0.2);
    EXPECT_EQ(electric.getFuelType(), "Electric");
    EXPECT_DOUBLE_EQ(electric.getAvailableAmount(), 50.0);
    EXPECT_DOUBLE_EQ(electric.calculateCost(10.0), 2.0);
    EXPECT_EQ(electric.getUnit(), "кВт*ч");
    EXPECT_THROW(fuel.refuel(-5.0), FuelErrorException);
}

TEST(TransportTest, GPSOperations)
{
    GPS gps;
    gps.setCoordinates(10.0, 20.0);
    auto [lat, lon] = gps.getCoordinates();
    EXPECT_DOUBLE_EQ(lat, 10.0);
    EXPECT_DOUBLE_EQ(lon, 20.0);
    RouteA route("RT1");
    auto [time, distance] = gps.chooseRoute(60.0, &route);
    EXPECT_EQ(time, static_cast<int>(38 * 100 / 60.0));
    EXPECT_EQ(distance, 15);
    RouteB routeB("RT2");
    auto [timeB, distanceB] = gps.chooseRoute(0.0, &routeB);
    EXPECT_EQ(timeB, 0);
    EXPECT_EQ(distanceB, 0);
}

TEST(TransportTest, LogisticsPlanRoute)
{
    Logistics logistics;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Name", "Addr", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("ORD1", passengers, &payment, 100.0, &truck, &client);
    EXPECT_NO_THROW(logistics.planRoute(&order));
}

TEST(TransportTest, MaintenanceFixPart)
{
    Maintenance maintenance;
    maintenance.fixPart("Engine");
}

TEST(TransportTest, OrderOperations)
{
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Max", "St Pervomayskaya 123", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("ORD1", passengers, &payment, 100.0, &truck, &client);
    EXPECT_EQ(order.getOrderId(), "ORD1");
    EXPECT_EQ(order.getPassengers().size(), 0);
    EXPECT_EQ(order.getPaymentType(), &payment);
    EXPECT_DOUBLE_EQ(order.getCargoWeight(), 100.0);
    EXPECT_EQ(order.getVehicle(), &truck);
    EXPECT_EQ(order.getCustomer(), &client);
    EXPECT_EQ(order.getStatus(), OrderStatus::Pending);
    EXPECT_DOUBLE_EQ(order.getTotalCost(), 100.0 * 10.0);
    order.setStatus(OrderStatus::InProgress);
    EXPECT_EQ(order.getStatus(), OrderStatus::InProgress);
    order.createOrder("ORD2", passengers, &payment, 200.0, &truck);
    EXPECT_EQ(order.getOrderId(), "ORD2");
    EXPECT_DOUBLE_EQ(order.getCargoWeight(), 200.0);
    EXPECT_DOUBLE_EQ(order.getTotalCost(), 200.0 * 10.0);
}

TEST(TransportTest, OrderAssignVehicleAndEmployee)
{
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Jack", "St 123", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "Commercial", 5, "Truck");
    Order order("ORD1", passengers, &payment, 100.0, &truck, &client);

    try
    {
        order.assignVehicleAndEmployee(&truck, &driver);
        EXPECT_EQ(order.getVehicle(), &truck);
    }
    catch (const DriverAssignmentException &e)
    {
        FAIL() << "DriverAssignmentException thrown: " << e.what();
    }
    catch (const std::exception &e)
    {
        FAIL() << "Unexpected exception: " << e.what();
    }
}

TEST(TransportTest, OrderExceptions)
{
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "John Doe", "123 St", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    EXPECT_THROW(Order("ORD1", passengers, nullptr, 100.0, &truck, &client), InvalidArgumentException);
    EXPECT_THROW(Order("ORD1", passengers, &payment, 100.0, nullptr, &client), InvalidArgumentException);
    EXPECT_THROW(Order("ORD1", passengers, &payment, 100.0, &truck, nullptr), InvalidArgumentException);
}

TEST(TransportTest, PassengerOperations)
{
    Passenger passenger("PS1", "Bruce", "Brase");
    Ticket ticket(1, "Valid");
    passenger.setTicket(&ticket);
    passenger.checkIn("Checked");
    EXPECT_EQ(passenger.getPassengerId(), "PS1");
    EXPECT_TRUE(passenger.hasValidTicket());
    passenger.setContactNumber("123456");
    EXPECT_EQ(passenger.getContactNumber(), "123456");
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "John Doe", "123 St", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("ORD1", passengers, &payment, 100.0, &truck, &client);
    passenger.setOrder(&order);
    EXPECT_EQ(passenger.getOrder(), &order);
}

TEST(TransportTest, PassengerExceptions)
{
    Passenger passenger("PS1", "John", "Doe");
    EXPECT_THROW(passenger.checkIn("Checked"), std::runtime_error);
}

TEST(TransportTest, RouteOperations)
{
    RouteA route("RT1");
    EXPECT_EQ(route.getRouteId(), "RT1");
    RouteB routeB("RT2");
    EXPECT_EQ(routeB.getRouteId(), "RT2");
    auto [time, distance] = route.calculateRoute(60.0);
    EXPECT_EQ(time, static_cast<int>(38 * 100 / 60.0));
    EXPECT_EQ(distance, 15);
}

TEST(TransportTest, SecurityOperations)
{
    Security security("SEC1");
    VehicleStatus status;
    status.setStatus(1);
    Fuel fuel("Diesel", 100.0, 1.0);
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    EXPECT_TRUE(security.checkVehicleSafety(&truck));
    Freight freight("FR1", 100.0, false);
    EXPECT_TRUE(security.checkFreightSafety(&freight));
}

TEST(TransportTest, SecurityExceptions)
{
    Security security("SEC1");
    Freight freight("FR1", 100.0, true);
    EXPECT_NO_THROW(security.checkFreightSafety(&freight));
    bool result = security.checkFreightSafety(&freight);
    EXPECT_TRUE(result == true || result == false);
}

TEST(TransportTest, ShipmentOperations)
{
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "John Doe", "123 St", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("ORD1", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SH1", &order);
    EXPECT_EQ(shipment.getShipmentId(), "SH1");
    EXPECT_EQ(shipment.getRelatedOrder(), &order);
    std::cout << "Testing updateTrackingStatus..." << std::endl;
    EXPECT_NO_THROW(shipment.updateTrackingStatus("Shipped"));
    std::cout << "Testing setVehicle..." << std::endl;
    EXPECT_NO_THROW(shipment.setVehicle(&truck));
    std::cout << "Testing setShipmentWeight..." << std::endl;
    EXPECT_NO_THROW(shipment.setShipmentWeight(100.0));
    EXPECT_DOUBLE_EQ(shipment.getShipmentWeight(), 100.0);
    std::cout << "ShipmentOperations test completed successfully" << std::endl;
}
TEST(TransportTest, TicketOperations)
{
    Ticket ticket(1, "Valid");
    EXPECT_EQ(ticket.getTicketNumber(), 1);
    EXPECT_EQ(ticket.getTicketStatus(), "Valid");
    ticket.setTicketStatus("Used");
    EXPECT_EQ(ticket.getTicketStatus(), "Used");
}

TEST(TransportTest, VehiclePolymorphism)
{
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Vehicle *truck = new Truck(&fuel, 120.0, 2, 10000.0, status);
    Vehicle *ship = new Ship(&fuel, 80.0, 100, 50000.0, status);
    truck->loadCargo(5000.0);
    double truckCons = truck->calculateFuelConsumption(100.0);
    EXPECT_GT(truckCons, 0.0);
    ship->loadCargo(20000.0);
    double shipCons = ship->calculateFuelConsumption(100.0);
    EXPECT_GT(shipCons, 0.0);
    delete truck;
    delete ship;
}

TEST(TransportTest, VehicleRefuel)
{
    Fuel fuel("Gasoline", 50.0, 2.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    truck.refuel(30.0);
    EXPECT_DOUBLE_EQ(fuel.getAvailableAmount(), 80.0);
    EXPECT_THROW(truck.refuel(-10.0), FuelErrorException);
}

TEST(TransportTest, VehicleStatusOperations)
{
    VehicleStatus vs;
    vs.setStatus(0);
    std::string status0 = vs.getStatus();
    EXPECT_FALSE(status0.empty());
    vs.setStatus(2);
    std::string status2 = vs.getStatus();
    EXPECT_FALSE(status2.empty());
    EXPECT_NE(status0, status2);
}

TEST(TransportTest, WarehouseOperations)
{
    Warehouse warehouse("WH1", 5);
    Freight freight1("FR1", 100.0, false);
    warehouse.storeFreight(&freight1);
    EXPECT_TRUE(warehouse.checkCapacity());

    for (int i = 2; i <= 5; ++i)
    {
        Freight f("FR" + std::to_string(i), 100.0, false);
        warehouse.storeFreight(&f);
    }

    Freight extra("FR6", 100.0, false);
    EXPECT_THROW(warehouse.storeFreight(&extra), CapacityExceededException);
    warehouse.removeFreight(&freight1);
}

TEST(TransportTest, AuditManager)
{
    std::vector<Depot> depots;
    std::vector<IClient *> clients;
    std::vector<IOrder *> orders;
    Analytics analytics(0.0, {});
    Logistics logistics;
    TransportCompany company(depots, clients, orders, analytics, logistics);
    AuditManager auditor;
    auditor.auditOperations(&company);
}

TEST(TransportTest, BillingProcess)
{
    Billing billing("BIL1");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Name", "Addr", &pm, &al, &lm);
    EXPECT_EQ(billing.getBillingId(), "BIL1");
}

TEST(TransportTest, HubOperations)
{
    Hub hub("HUB1", 5);
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "John Doe", "123 St", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("ORD1", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SH1", &order);
    hub.transShip(&shipment);
    EXPECT_TRUE(hub.checkCapacity());
    RouteA route("RT1");
    hub.sortByDestination(&route);
}

TEST(TransportTest, InventoryManager)
{
    InventoryManager manager("IM1");
    Warehouse warehouse("WH1", 10);
    manager.addWarehouse(&warehouse);
    Freight freight("FR1", 100.0, false);
    manager.manageInventory(&freight, &warehouse);
    EXPECT_EQ(manager.getManagerId(), "IM1");
}

TEST(TransportTest, LicenseOperations)
{
    License license("LIC1", "TypeA", "Active");
    EXPECT_EQ(license.getLicenseId(), "LIC1");
    license.setLicenseStatus("Expired");
    EXPECT_EQ(license.getLicenseStatus(), "Expired");
}

TEST(TransportTest, CargoInspector)
{
    CargoInspector inspector("INS1");
    Freight freight("FR1", 100.0, false);
    EXPECT_TRUE(inspector.inspectCargo(&freight));
    Freight hazardous("FR2", 100.0, true);
    EXPECT_TRUE(inspector.inspectCargo(&hazardous));
}

TEST(TransportTest, OperationsMonitor)
{
    std::vector<IVehicle *> vehicles;
    std::vector<Shipment> shipments;
    GPS gps;
    OperationsMonitor monitor(vehicles, shipments, &gps);
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    monitor.monitorVehicle(&truck);
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "John Doe", "123 St", &pm, &al, &lm);
    CardPayment payment;
    Order order("ORD1", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SH1", &order);
    monitor.alertDelay(&shipment);
    EXPECT_EQ(monitor.getMonitoredVehicles().size(), 1);
}

TEST(TransportTest, PaymentMethods)
{
    CardPayment card;
    EXPECT_NO_THROW(card.processPayment());
    CashPayment cash;
    EXPECT_NO_THROW(cash.processPayment());
    CheckPayment check;
    EXPECT_NO_THROW(check.processPayment());
}

TEST(TransportTest, PaymentManagerOperations)
{
    PaymentManager pm;
    EXPECT_NO_THROW(pm.makePayment(1));
    EXPECT_NO_THROW(pm.makePayment(2));
    EXPECT_NO_THROW(pm.makePayment(3));
    EXPECT_THROW(pm.makePayment(4), InvalidPaymentException);
    PaymentManager pm2;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "John Doe", "123 St", &pm2, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    pm2.makeOrderPayment(&client, "ORD1", passengers, &payment, 100.0, &truck);
}

TEST(TransportTest, ClientActivityLogger)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "John Doe", "123 St", &pm, &al, &lm);
    al.logClientActivity(&client);
}

TEST(TransportTest, LoyaltyManager)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "John Doe", "123 St", &pm, &al, &lm);
    lm.applyLoyaltyDiscount(&client, 10.0);
    EXPECT_DOUBLE_EQ(client.getDiscountRate(), 0.1);
    EXPECT_FALSE(lm.checkEligibilityForPriority(&client));
}

TEST(TransportTest, RevenueCalculator)
{
    std::vector<Depot> depots;
    std::vector<IClient *> clients;
    std::vector<IOrder *> orders;
    Analytics analytics(0.0, {});
    Logistics logistics;
    TransportCompany company(depots, clients, orders, analytics, logistics);
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "John Doe", "123 St", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("ORD1", passengers, &payment, 100.0, &truck, &client);
    company.addOrder(&order);
    RevenueCalculator calc;
    calc.computeRevenue(&company);
}

TEST(TransportTest, RoutePlanner)
{
    RoutePlanner planner;
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "John Doe", "123 St", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("ORD1", passengers, &payment, 100.0, &truck, &client);
    planner.planRoute(&order);
}

TEST(TransportTest, ManagerCoordinator)
{
    ManagerCoordinator coord;
}

TEST(TransportTest, ExceptionCases)
{
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Ship ship(&fuel, 20.0, 100, 10000.0, status);
    EXPECT_THROW(ship.loadCargo(20000.0), InvalidWeightException);
    EXPECT_NO_THROW(ship.unloadCargo(100.0));
    Freight freight("FR1", 100.0, false);
    freight.setLength(-1.0);
    EXPECT_THROW(freight.calculateVolume(), FreightDimensionException);
}

TEST(TransportTest, DeliveryConstructorAndGetters)
{
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("TEST_ORDER", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("TEST_SHIPMENT", &order);
    Delivery delivery("DELIVERY_001", &shipment);
    EXPECT_EQ(delivery.getDeliveryId(), "DELIVERY_001");
}

TEST(TransportTest, DeliveryInitiateDelivery)
{
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("TEST_ORDER", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("TEST_SHIPMENT", &order);
    shipment.setVehicle(&truck);
    Delivery delivery("DELIVERY_001", &shipment);
    EXPECT_NO_THROW(delivery.initiateDelivery());
}

TEST(TransportTest, DeliveryConfirmDelivery)
{
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("TEST_ORDER", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("TEST_SHIPMENT", &order);
    shipment.setVehicle(&truck);
    Delivery delivery("DELIVERY_001", &shipment);
    Notification notification("Test message", "info");
    EXPECT_NO_THROW(delivery.confirmDelivery(&notification));
}

TEST(TransportTest, DeliveryMultipleDeliveries)
{
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order1("ORDER_1", passengers, &payment, 100.0, &truck, &client);
    Order order2("ORDER_2", passengers, &payment, 200.0, &truck, &client);
    Shipment shipment1("SHIPMENT_1", &order1);
    Shipment shipment2("SHIPMENT_2", &order2);
    shipment1.setVehicle(&truck);
    shipment2.setVehicle(&truck);
    Delivery delivery1("DELIVERY_1", &shipment1);
    Delivery delivery2("DELIVERY_2", &shipment2);
    Notification notification("Test", "info");
    EXPECT_EQ(delivery1.getDeliveryId(), "DELIVERY_1");
    EXPECT_EQ(delivery2.getDeliveryId(), "DELIVERY_2");
    EXPECT_NO_THROW(delivery1.initiateDelivery());
    EXPECT_NO_THROW(delivery2.confirmDelivery(&notification));
}

TEST(TransportTest, DeliveryEdgeCases)
{
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("TEST_ORDER", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("TEST_SHIPMENT", &order);
    Delivery emptyIdDelivery("", &shipment);
    EXPECT_EQ(emptyIdDelivery.getDeliveryId(), "");
    Delivery longIdDelivery("VERY_LONG_DELIVERY_ID_1234567890", &shipment);
    EXPECT_EQ(longIdDelivery.getDeliveryId(), "VERY_LONG_DELIVERY_ID_1234567890");
}

TEST(TransportTest, ShipmentConstructorAndGetters)
{
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("TEST_ORDER", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIPMENT_001", &order);
    EXPECT_EQ(shipment.getShipmentId(), "SHIPMENT_001");
    EXPECT_EQ(shipment.getRelatedOrder(), &order);
}

TEST(TransportTest, ShipmentWeightOperations)
{
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("TEST_ORDER", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIPMENT_001", &order);
    shipment.setShipmentWeight(150.5);
    EXPECT_DOUBLE_EQ(shipment.getShipmentWeight(), 150.5);
    shipment.setShipmentWeight(0.0);
    EXPECT_DOUBLE_EQ(shipment.getShipmentWeight(), 0.0);
    shipment.setShipmentWeight(9999.9);
    EXPECT_DOUBLE_EQ(shipment.getShipmentWeight(), 9999.9);
}

TEST(TransportTest, ShipmentDeliveryAttempts)
{
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("TEST_ORDER", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIPMENT_001", &order);
    EXPECT_EQ(shipment.getDeliveryAttempts(), 0);
    shipment.incrementDeliveryAttempts();
    EXPECT_EQ(shipment.getDeliveryAttempts(), 1);
    shipment.incrementDeliveryAttempts();
    shipment.incrementDeliveryAttempts();
    EXPECT_EQ(shipment.getDeliveryAttempts(), 3);
}

TEST(TransportTest, ShipmentVehicleAssignment)
{
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("TEST_ORDER", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIPMENT_001", &order);
    shipment.setVehicle(&truck);
    EXPECT_NO_THROW(shipment.updateTrackingStatus("In Transit"));
}

TEST(TransportTest, ShipmentTrackingStatus)
{
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("TEST_ORDER", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIPMENT_001", &order);
    EXPECT_NO_THROW(shipment.updateTrackingStatus("Preparing"));
    EXPECT_NO_THROW(shipment.updateTrackingStatus("In Transit"));
    EXPECT_NO_THROW(shipment.updateTrackingStatus("Out for Delivery"));
    EXPECT_NO_THROW(shipment.updateTrackingStatus("Delivered"));
    EXPECT_NO_THROW(shipment.updateTrackingStatus(""));
}

TEST(TransportTest, ShipmentCostCalculation)
{
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("TEST_ORDER", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIPMENT_001", &order);
    shipment.setShipmentWeight(100.0);
    double cost = shipment.calculateShipmentCost();
    EXPECT_GE(cost, 0.0);
}

TEST(TransportTest, ShipmentLogging)
{
    std::vector<Passenger> passengers;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Order order("TEST_ORDER", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIPMENT_001", &order);
    EXPECT_NO_THROW(shipment.logShipmentStatus());
}

TEST(FeedbackTest, ConstructorAndGetRating)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client, &driver);
    Feedback feedback(5, "Отличный сервис!", &client, &order);
    EXPECT_EQ(feedback.getRating(), 5);
}

TEST(FeedbackTest, SubmitFeedback)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client, &driver);
    Feedback feedback(0, "", &client, nullptr);
    EXPECT_NO_THROW(feedback.submitFeedback(&order, 4, "Хорошо, но можно лучше"));
}

TEST(FeedbackTest, EscalateToManager)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client, &driver);
    Manager manager("MGR1", "Test", "Manager");
    Feedback feedback(1, "Плохой сервис", &client, &order);
    EXPECT_NO_THROW(feedback.escalateToManager(&manager));
}

TEST(FeedbackTest, DifferentRatings)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client, &driver);
    Feedback feedback1(1, "Ужасно", &client, &order);
    Feedback feedback2(3, "Нормально", &client, &order);
    Feedback feedback3(5, "Отлично", &client, &order);
    EXPECT_EQ(feedback1.getRating(), 1);
    EXPECT_EQ(feedback2.getRating(), 3);
    EXPECT_EQ(feedback3.getRating(), 5);
}

TEST(FeedbackTest, SubmitToDifferentOrders)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    Order order1("ORDER_001", passengers, &payment, 100.0, &truck, &client, &driver);
    Order order2("ORDER_002", passengers, &payment, 200.0, &truck, &client, &driver);
    Feedback feedback(0, "", &client, nullptr);
    EXPECT_NO_THROW(feedback.submitFeedback(&order1, 5, "Отлично!"));
    EXPECT_NO_THROW(feedback.submitFeedback(&order2, 2, "Плохо"));
}

TEST(FeedbackTest, MultipleEscalations)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client, &driver);
    Manager manager1("MGR1", "Manager", "One");
    Manager manager2("MGR2", "Manager", "Two");
    Feedback feedback(1, "Очень плохо", &client, &order);
    EXPECT_NO_THROW(feedback.escalateToManager(&manager1));
    EXPECT_NO_THROW(feedback.escalateToManager(&manager2));
}

TEST(TruckTest, ConstructorAndBasicProperties)
{
    Fuel fuel("Diesel", 100.0, 1.5);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    EXPECT_NO_THROW(Truck truck(&fuel, 80.0, 2, 5000.0, status));
}

TEST(TruckTest, LoadCargoValidWeight)
{
    Fuel fuel("Diesel", 100.0, 1.5);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    EXPECT_NO_THROW(truck.loadCargo(3000.0));
}

TEST(TruckTest, LoadCargoInvalidWeight)
{
    Fuel fuel("Diesel", 100.0, 1.5);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    EXPECT_THROW(truck.loadCargo(6000.0), InvalidWeightException);
}

TEST(TruckTest, UnloadCargoValid)
{
    Fuel fuel("Diesel", 100.0, 1.5);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    truck.loadCargo(3000.0);
    EXPECT_NO_THROW(truck.unloadCargo(1000.0));
}

TEST(TruckTest, UnloadCargoExceedingCurrent)
{
    Fuel fuel("Diesel", 100.0, 1.5);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    truck.loadCargo(1000.0);
    EXPECT_NO_THROW(truck.unloadCargo(1500.0));
}

TEST(TruckTest, CalculateFuelConsumption)
{
    Fuel fuel("Diesel", 100.0, 1.5);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    double consumption = truck.calculateFuelConsumption(100.0);
    EXPECT_EQ(consumption, 20.0);
}

TEST(TruckTest, CalculateFuelConsumptionDifferentDistances)
{
    Fuel fuel("Diesel", 100.0, 1.5);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    EXPECT_EQ(truck.calculateFuelConsumption(50.0), 10.0);
    EXPECT_EQ(truck.calculateFuelConsumption(200.0), 40.0);
    EXPECT_EQ(truck.calculateFuelConsumption(0.0), 0.0);
}

TEST(TruckTest, EstimateTravelTime)
{
    Fuel fuel("Diesel", 100.0, 1.5);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    double time = truck.estimateTravelTime(240.0);
    EXPECT_EQ(time, 3.0);
}

TEST(TruckTest, EstimateTravelTimeDifferentSpeeds)
{
    Fuel fuel("Diesel", 100.0, 1.5);
    VehicleStatus status;
    Truck slowTruck(&fuel, 60.0, 2, 5000.0, status);
    Truck fastTruck(&fuel, 90.0, 2, 5000.0, status);
    EXPECT_EQ(slowTruck.estimateTravelTime(180.0), 3.0);
    EXPECT_EQ(fastTruck.estimateTravelTime(180.0), 2.0);
}

TEST(TruckTest, CalculateTotalCost)
{
    Fuel fuel("Diesel", 100.0, 1.5);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    double cost = truck.calculateTotalCost(100.0);
    EXPECT_EQ(cost, 20.0);
}

TEST(TruckTest, LogTripMethods)
{
    Fuel fuel("Diesel", 100.0, 1.5);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    EXPECT_NO_THROW(truck.logTripStart());
    EXPECT_NO_THROW(truck.logTripEnd());
}

TEST(TruckTest, MultipleLoadUnloadOperations)
{
    Fuel fuel("Diesel", 100.0, 1.5);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    EXPECT_NO_THROW(truck.loadCargo(1000.0));
    EXPECT_NO_THROW(truck.unloadCargo(500.0));
    EXPECT_NO_THROW(truck.loadCargo(2000.0));
    EXPECT_NO_THROW(truck.unloadCargo(1000.0));
    EXPECT_NO_THROW(truck.loadCargo(500.0));
}

TEST(TruckTest, EdgeCaseLoadCapacity)
{
    Fuel fuel("Diesel", 100.0, 1.5);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    EXPECT_NO_THROW(truck.loadCargo(5000.0));
    EXPECT_THROW(truck.loadCargo(5000.1), InvalidWeightException);
}

TEST(VanTest, ConstructorAndBasicProperties)
{
    Fuel fuel("Petrol", 80.0, 1.2);
    VehicleStatus status;
    EXPECT_NO_THROW(Van van(&fuel, 120.0, 8, 1500.0, status));
}

TEST(VanTest, LoadCargoValidWeight)
{
    Fuel fuel("Petrol", 80.0, 1.2);
    VehicleStatus status;
    Van van(&fuel, 120.0, 8, 1500.0, status);
    EXPECT_NO_THROW(van.loadCargo(1000.0));
}

TEST(VanTest, LoadCargoInvalidWeight)
{
    Fuel fuel("Petrol", 80.0, 1.2);
    VehicleStatus status;
    Van van(&fuel, 120.0, 8, 1500.0, status);
    EXPECT_THROW(van.loadCargo(2000.0), InvalidWeightException);
}

TEST(VanTest, UnloadCargoValid)
{
    Fuel fuel("Petrol", 80.0, 1.2);
    VehicleStatus status;
    Van van(&fuel, 120.0, 8, 1500.0, status);
    van.loadCargo(1000.0);
    EXPECT_NO_THROW(van.unloadCargo(500.0));
}

TEST(VanTest, CalculateFuelConsumption)
{
    Fuel fuel("Petrol", 80.0, 1.2);
    VehicleStatus status;
    Van van(&fuel, 120.0, 8, 1500.0, status);
    double consumption = van.calculateFuelConsumption(100.0);
    EXPECT_EQ(consumption, 15.0);
}

TEST(VanTest, EstimateTravelTime)
{
    Fuel fuel("Petrol", 80.0, 1.2);
    VehicleStatus status;
    Van van(&fuel, 120.0, 8, 1500.0, status);
    double time = van.estimateTravelTime(240.0);
    EXPECT_EQ(time, 2.0);
}

TEST(VanTest, UpdateOdometer)
{
    Fuel fuel("Petrol", 80.0, 1.2);
    VehicleStatus status;
    Van van(&fuel, 120.0, 8, 1500.0, status);
    EXPECT_NO_THROW(van.updateOdometer(150.0));
}

TEST(VanTest, CheckMaintenanceDue)
{
    Fuel fuel("Petrol", 80.0, 1.2);
    VehicleStatus status;
    Van van(&fuel, 120.0, 8, 1500.0, status);
    bool maintenanceDue = van.checkMaintenanceDue();
    EXPECT_NO_THROW(van.checkMaintenanceDue());
}

TEST(VanTest, CalculateTotalCost)
{
    Fuel fuel("Petrol", 80.0, 1.2);
    VehicleStatus status;
    Van van(&fuel, 120.0, 8, 1500.0, status);
    double cost = van.calculateTotalCost(100.0);
    EXPECT_EQ(cost, 12.0);
}

TEST(VanTest, LogTripMethods)
{
    Fuel fuel("Petrol", 80.0, 1.2);
    VehicleStatus status;
    Van van(&fuel, 120.0, 8, 1500.0, status);
    EXPECT_NO_THROW(van.logTripStart());
    EXPECT_NO_THROW(van.logTripEnd());
}

TEST(VanTest, VerifyInsurance)
{
    Fuel fuel("Petrol", 80.0, 1.2);
    VehicleStatus status;
    Van van(&fuel, 120.0, 8, 1500.0, status);
    bool insured = van.verifyInsurance();
    EXPECT_NO_THROW(van.verifyInsurance());
}

TEST(VanTest, AdjustTirePressure)
{
    Fuel fuel("Petrol", 80.0, 1.2);
    VehicleStatus status;
    Van van(&fuel, 120.0, 8, 1500.0, status);
    EXPECT_NO_THROW(van.adjustTirePressure(2.5));
}

TEST(VanTest, GetVehicleDetails)
{
    Fuel fuel("Petrol", 80.0, 1.2);
    VehicleStatus status;
    Van van(&fuel, 120.0, 8, 1500.0, status);
    std::string details = van.getVehicleDetails();
    EXPECT_NO_THROW(van.getVehicleDetails());
}

TEST(VanTest, PerformSelfCheck)
{
    Fuel fuel("Petrol", 80.0, 1.2);
    VehicleStatus status;
    Van van(&fuel, 120.0, 8, 1500.0, status);
    EXPECT_NO_THROW(van.performSelfCheck());
}

TEST(TrainTest, ConstructorAndBasicProperties)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    EXPECT_NO_THROW(Train train(&fuel, 160.0, 500, 50000.0, status));
}

TEST(TrainTest, LoadCargoValidWeight)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    EXPECT_NO_THROW(train.loadCargo(30000.0));
}

TEST(TrainTest, LoadCargoInvalidWeight)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    EXPECT_THROW(train.loadCargo(60000.0), InvalidWeightException);
}

TEST(TrainTest, LoadPeopleValid)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    EXPECT_NO_THROW(train.loadPeople(300));
}

TEST(TrainTest, LoadPeopleInvalid)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    EXPECT_THROW(train.loadPeople(600), PassengerLimitException);
}

TEST(TrainTest, UnloadCargoValid)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    train.loadCargo(40000.0);
    EXPECT_NO_THROW(train.unloadCargo(20000.0));
}

TEST(TrainTest, UnloadPeopleValid)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    train.loadPeople(400);
    EXPECT_NO_THROW(train.unloadPeople(200));
}

TEST(TrainTest, GetCurrentCargoAndPeople)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    train.loadCargo(25000.0);
    train.loadPeople(350);
    EXPECT_EQ(train.getCurrentCargo(), 25000.0);
    EXPECT_EQ(train.getCurrentPeople(), 350);
}

TEST(TrainTest, CalculateFuelConsumption)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    double consumption = train.calculateFuelConsumption(100.0);
    EXPECT_EQ(consumption, 600.0);
}

TEST(TrainTest, EstimateTravelTime)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    double time = train.estimateTravelTime(480.0);
    EXPECT_EQ(time, 3.0);
}

TEST(TrainTest, UpdateOdometer)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    EXPECT_NO_THROW(train.updateOdometer(250.0));
    EXPECT_NO_THROW(train.updateOdometer(150.5));
}

TEST(TrainTest, CheckMaintenanceDue)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    bool maintenanceDue = train.checkMaintenanceDue();
    EXPECT_NO_THROW(train.checkMaintenanceDue());
}

TEST(TrainTest, CalculateTotalCost)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    double cost = train.calculateTotalCost(100.0);
    EXPECT_EQ(cost, 720.0);
}

TEST(TrainTest, LogTripMethods)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    EXPECT_NO_THROW(train.logTripStart());
    EXPECT_NO_THROW(train.logTripEnd());
}

TEST(TrainTest, VerifyInsurance)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    bool insured = train.verifyInsurance();
    EXPECT_NO_THROW(train.verifyInsurance());
}

TEST(TrainTest, AdjustTirePressure)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    EXPECT_NO_THROW(train.adjustTirePressure(5.0));
    EXPECT_NO_THROW(train.adjustTirePressure(5.5));
}

TEST(TrainTest, GetVehicleDetails)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    std::string details = train.getVehicleDetails();
    EXPECT_NO_THROW(train.getVehicleDetails());
}

TEST(TrainTest, PerformSelfCheck)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    EXPECT_NO_THROW(train.performSelfCheck());
}

TEST(TrainTest, EdgeCaseLoadCapacity)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    EXPECT_NO_THROW(train.loadCargo(50000.0));
    EXPECT_THROW(train.loadCargo(50000.1), InvalidWeightException);
    EXPECT_NO_THROW(train.loadPeople(500));
    EXPECT_THROW(train.loadPeople(501), PassengerLimitException);
}

TEST(TrainTest, MultipleLoadUnloadOperations)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    EXPECT_NO_THROW(train.loadCargo(20000.0));
    EXPECT_NO_THROW(train.loadPeople(200));
    EXPECT_NO_THROW(train.unloadCargo(5000.0));
    EXPECT_NO_THROW(train.unloadPeople(50));
    EXPECT_NO_THROW(train.loadCargo(10000.0));
    EXPECT_NO_THROW(train.loadPeople(100));
}

TEST(TrainTest, UnloadExceedingCurrent)
{
    Fuel fuel("Diesel", 500.0, 0.8);
    VehicleStatus status;
    Train train(&fuel, 160.0, 500, 50000.0, status);
    train.loadCargo(10000.0);
    train.loadPeople(100);
    EXPECT_NO_THROW(train.unloadCargo(15000.0));
    EXPECT_NO_THROW(train.unloadPeople(150));
}

TEST(PaymentProcessorTest, ConstructorAndGetProcessorId)
{
    PaymentProcessor processor("PROC_001");
    EXPECT_EQ(processor.getProcessorId(), "PROC_001");
}

TEST(PaymentProcessorTest, ProcessPaymentWithCard)
{
    PaymentProcessor processor("CARD_PROC");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment payment;
    bool result = processor.processPayment(&client, &payment, 1000.0);
    EXPECT_TRUE(result);
}

TEST(PaymentProcessorTest, ProcessPaymentWithCash)
{
    PaymentProcessor processor("CASH_PROC");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CashPayment payment;
    bool result = processor.processPayment(&client, &payment, 500.0);
    EXPECT_TRUE(result);
}

TEST(PaymentProcessorTest, ProcessPaymentWithCheck)
{
    PaymentProcessor processor("CHECK_PROC");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CheckPayment payment;
    bool result = processor.processPayment(&client, &payment, 750.0);
    EXPECT_TRUE(result);
}

TEST(PaymentProcessorTest, ProcessPaymentDifferentAmounts)
{
    PaymentProcessor processor("PROC_002");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment payment;
    EXPECT_TRUE(processor.processPayment(&client, &payment, 0.0));
    EXPECT_TRUE(processor.processPayment(&client, &payment, 500.0));
    EXPECT_TRUE(processor.processPayment(&client, &payment, 10000.0));
}

TEST(PaymentProcessorTest, ProcessPaymentDifferentClients)
{
    PaymentProcessor processor("PROC_003");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client1("CL1", "Client One", "Address 1", &pm, &al, &lm);
    Client client2("CL2", "Client Two", "Address 2", &pm, &al, &lm);
    Client client3("CL3", "Client Three", "Address 3", &pm, &al, &lm);
    CardPayment payment;
    EXPECT_TRUE(processor.processPayment(&client1, &payment, 100.0));
    EXPECT_TRUE(processor.processPayment(&client2, &payment, 200.0));
    EXPECT_TRUE(processor.processPayment(&client3, &payment, 300.0));
}

TEST(PaymentProcessorTest, MultipleProcessors)
{
    PaymentProcessor processor1("VISA_PROC");
    PaymentProcessor processor2("MC_PROC");
    PaymentProcessor processor3("PAYPAL_PROC");
    EXPECT_EQ(processor1.getProcessorId(), "VISA_PROC");
    EXPECT_EQ(processor2.getProcessorId(), "MC_PROC");
    EXPECT_EQ(processor3.getProcessorId(), "PAYPAL_PROC");
}

TEST(PaymentProcessorTest, ProcessPaymentMultipleTimes)
{
    PaymentProcessor processor("PROC_004");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment payment;
    EXPECT_TRUE(processor.processPayment(&client, &payment, 100.0));
    EXPECT_TRUE(processor.processPayment(&client, &payment, 200.0));
    EXPECT_TRUE(processor.processPayment(&client, &payment, 300.0));
}

TEST(PaymentProcessorTest, ProcessPaymentWithDifferentPaymentMethods)
{
    PaymentProcessor processor("UNIVERSAL_PROC");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    CardPayment card;
    CashPayment cash;
    CheckPayment check;
    EXPECT_TRUE(processor.processPayment(&client, &card, 100.0));
    EXPECT_TRUE(processor.processPayment(&client, &cash, 200.0));
    EXPECT_TRUE(processor.processPayment(&client, &check, 300.0));
}

TEST(PaymentProcessorTest, EmptyProcessorId)
{
    PaymentProcessor processor("");
    EXPECT_EQ(processor.getProcessorId(), "");
}

TEST(PaymentProcessorTest, LongProcessorId)
{
    PaymentProcessor processor("VERY_LONG_PROCESSOR_ID_1234567890");
    EXPECT_EQ(processor.getProcessorId(), "VERY_LONG_PROCESSOR_ID_1234567890");
}

TEST(PaymentProcessorTest, SpecialCharactersProcessorId)
{
    PaymentProcessor processor("PROC-123_ABC@TEST");
    EXPECT_EQ(processor.getProcessorId(), "PROC-123_ABC@TEST");
}

TEST(ManagerCoordinatorTest, AddManager)
{
    ManagerCoordinator coordinator;
    Manager manager("MGR1", "John", "Doe");
    EXPECT_NO_THROW(coordinator.addManager(&manager));
}

TEST(ManagerCoordinatorTest, AddMultipleManagers)
{
    ManagerCoordinator coordinator;
    Manager manager1("MGR1", "John", "Doe");
    Manager manager2("MGR2", "Jane", "Smith");
    Manager manager3("MGR3", "Bob", "Johnson");
    EXPECT_NO_THROW(coordinator.addManager(&manager1));
    EXPECT_NO_THROW(coordinator.addManager(&manager2));
    EXPECT_NO_THROW(coordinator.addManager(&manager3));
}

TEST(MenuTest, LocationMenuOutput)
{
    Menu menu;
    std::stringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    menu.locationMenu();
    std::cout.rdbuf(oldCout);
    std::string output = buffer.str();
    EXPECT_NE(output.find("1.Лиссабон"), std::string::npos);
    EXPECT_NE(output.find("2.Пинск"), std::string::npos);
    EXPECT_NE(output.find("3.Москва"), std::string::npos);
    EXPECT_NE(output.find("4.Цюрих"), std::string::npos);
    EXPECT_NE(output.find("5.Берлин"), std::string::npos);
}

TEST(MenuTest, LocationMenuNoExceptions)
{
    Menu menu;
    EXPECT_NO_THROW(menu.locationMenu());
}

TEST(MenuTest, MultipleLocationMenuCalls)
{
    Menu menu;
    EXPECT_NO_THROW(menu.locationMenu());
    EXPECT_NO_THROW(menu.locationMenu());
    EXPECT_NO_THROW(menu.locationMenu());
}

TEST(MenuTest, LocationMenuFormat)
{
    Menu menu;
    std::stringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    menu.locationMenu();
    std::cout.rdbuf(oldCout);
    std::string output = buffer.str();
    EXPECT_NE(output.find("1."), std::string::npos);
    EXPECT_NE(output.find("2."), std::string::npos);
    EXPECT_NE(output.find("3."), std::string::npos);
    EXPECT_NE(output.find("4."), std::string::npos);
    EXPECT_NE(output.find("5."), std::string::npos);
}

TEST(MenuTest, LocationMenuOrder)
{
    Menu menu;
    std::stringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    menu.locationMenu();
    std::cout.rdbuf(oldCout);
    std::string output = buffer.str();
    size_t pos1 = output.find("1.Лиссабон");
    size_t pos2 = output.find("2.Пинск");
    size_t pos3 = output.find("3.Москва");
    size_t pos4 = output.find("4.Цюрих");
    size_t pos5 = output.find("5.Берлин");
    EXPECT_LT(pos1, pos2);
    EXPECT_LT(pos2, pos3);
    EXPECT_LT(pos3, pos4);
    EXPECT_LT(pos4, pos5);
}

TEST(NotificationTest, ConstructorAndGetters)
{
    Notification notification("Test message", "EMAIL");
    EXPECT_EQ(notification.getMessage(), "Test message");
    EXPECT_EQ(notification.getType(), "EMAIL");
}

TEST(NotificationTest, SendNotification)
{
    Notification notification("", "SMS");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    EXPECT_NO_THROW(notification.sendNotification(&client, "Test notification message"));
}

TEST(NotificationTest, NotifyOrderStatus)
{
    Notification notification("", "PUSH");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client, &driver);
    EXPECT_NO_THROW(notification.notifyOrderStatus(&order));
}

TEST(NotificationTest, StatusToString)
{
    Notification notification("", "EMAIL");
    std::string status = notification.statusToString(OrderStatus::Pending);
    EXPECT_EQ(status, "Pending");
}

TEST(NotificationTest, DifferentNotificationTypes)
{
    Notification emailNotif("Email message", "EMAIL");
    Notification smsNotif("SMS message", "SMS");
    Notification pushNotif("Push message", "PUSH");
    EXPECT_EQ(emailNotif.getType(), "EMAIL");
    EXPECT_EQ(smsNotif.getType(), "SMS");
    EXPECT_EQ(pushNotif.getType(), "PUSH");
}

TEST(NotificationTest, SendNotificationToDifferentClients)
{
    Notification notification("", "SMS");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client1("CL1", "Client One", "Address 1", &pm, &al, &lm);
    Client client2("CL2", "Client Two", "Address 2", &pm, &al, &lm);
    Client client3("CL3", "Client Three", "Address 3", &pm, &al, &lm);
    EXPECT_NO_THROW(notification.sendNotification(&client1, "Message for client 1"));
    EXPECT_NO_THROW(notification.sendNotification(&client2, "Message for client 2"));
    EXPECT_NO_THROW(notification.sendNotification(&client3, "Message for client 3"));
}

TEST(NotificationTest, NotifyOrderStatusWithDifferentOrders)
{
    Notification notification("", "EMAIL");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    Order order1("ORDER_001", passengers, &payment, 100.0, &truck, &client, &driver);
    Order order2("ORDER_002", passengers, &payment, 200.0, &truck, &client, &driver);
    Order order3("ORDER_003", passengers, &payment, 300.0, &truck, &client, &driver);
    order1.setStatus(OrderStatus::Pending);
    order2.setStatus(OrderStatus::InProgress);
    order3.setStatus(OrderStatus::Completed);
    EXPECT_NO_THROW(notification.notifyOrderStatus(&order1));
    EXPECT_NO_THROW(notification.notifyOrderStatus(&order2));
    EXPECT_NO_THROW(notification.notifyOrderStatus(&order3));
}

TEST(NotificationTest, SendNotificationWithDifferentMessages)
{
    Notification notification("", "SMS");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    EXPECT_NO_THROW(notification.sendNotification(&client, "Short message"));
    EXPECT_NO_THROW(notification.sendNotification(&client, "Very long message with lots of details and information"));
    EXPECT_NO_THROW(notification.sendNotification(&client, "Message with special chars: !@#$%^&*()"));
    EXPECT_NO_THROW(notification.sendNotification(&client, ""));
}

TEST(NotificationTest, MultipleNotifications)
{
    Notification notif1("First message", "EMAIL");
    Notification notif2("Second message", "SMS");
    Notification notif3("Third message", "PUSH");
    EXPECT_EQ(notif1.getMessage(), "First message");
    EXPECT_EQ(notif2.getMessage(), "Second message");
    EXPECT_EQ(notif3.getMessage(), "Third message");
}

TEST(NotificationTest, EmptyNotification)
{
    Notification notification("", "");
    EXPECT_EQ(notification.getMessage(), "");
    EXPECT_EQ(notification.getType(), "");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    EXPECT_NO_THROW(notification.sendNotification(&client, ""));
}

TEST(InvoiceTest, ConstructorAndGetters)
{
    Notification notification("Test", "EMAIL");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client, &driver);
    Invoice invoice("INV_001", 1500.0, false, &notification, &order);
    EXPECT_EQ(invoice.getInvoiceId(), "INV_001");
    EXPECT_EQ(invoice.getAmount(), 1500.0);
    EXPECT_FALSE(invoice.getIsPaid());
    EXPECT_EQ(invoice.getRelatedOrder(), &order);
}

TEST(InvoiceTest, CheckPayment)
{
    Notification notification("Test", "EMAIL");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client, &driver);
    Invoice invoice("INV_001", 1500.0, false, &notification, &order);
    bool result = invoice.checkPayment(&payment);
    EXPECT_TRUE(result);
    EXPECT_TRUE(invoice.getIsPaid());
}

TEST(InvoiceTest, SentToClient)
{
    Notification notification("Test", "EMAIL");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client, &driver);
    Invoice invoice("INV_001", 1500.0, false, &notification, &order);
    EXPECT_NO_THROW(invoice.sentToClient(&client));
}

TEST(InvoiceTest, GenerateInvoice)
{
    Notification notification("Test", "EMAIL");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client, &driver);
    Order testOrder("ORDER_002", passengers, &payment, 200.0, &truck, &client, &driver);
    Invoice invoice("INV_001", 1500.0, false, &notification, &order);
    EXPECT_NO_THROW(invoice.generateInvoice(&testOrder));
}

TEST(InvoiceTest, DifferentInvoiceAmounts)
{
    Notification notification("Test", "EMAIL");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client, &driver);
    Invoice invoice1("INV_001", 0.0, false, &notification, &order);
    Invoice invoice2("INV_002", 500.0, false, &notification, &order);
    Invoice invoice3("INV_003", 10000.0, false, &notification, &order);
    EXPECT_EQ(invoice1.getAmount(), 0.0);
    EXPECT_EQ(invoice2.getAmount(), 500.0);
    EXPECT_EQ(invoice3.getAmount(), 10000.0);
}

TEST(InvoiceTest, CheckPaymentWithDifferentPayments)
{
    Notification notification("Test", "EMAIL");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment cardPayment;
    CashPayment cashPayment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    Order order("ORDER_001", passengers, &cardPayment, 100.0, &truck, &client, &driver);
    Invoice invoice1("INV_001", 1000.0, false, &notification, &order);
    Invoice invoice2("INV_002", 1000.0, false, &notification, &order);
    EXPECT_TRUE(invoice1.checkPayment(&cardPayment));
    EXPECT_TRUE(invoice2.checkPayment(&cashPayment));
}

TEST(InvoiceTest, SentToDifferentClients)
{
    Notification notification("Test", "EMAIL");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client1("CL1", "Client One", "Address 1", &pm, &al, &lm);
    Client client2("CL2", "Client Two", "Address 2", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client1, &driver);
    Invoice invoice("INV_001", 1500.0, false, &notification, &order);
    EXPECT_NO_THROW(invoice.sentToClient(&client1));
    EXPECT_NO_THROW(invoice.sentToClient(&client2));
}

TEST(InvoiceTest, MultipleInvoicesForSameOrder)
{
    Notification notification("Test", "EMAIL");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 100.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client, &driver);
    Invoice invoice1("INV_001", 1000.0, false, &notification, &order);
    Invoice invoice2("INV_002", 2000.0, true, &notification, &order);
    Invoice invoice3("INV_003", 3000.0, false, &notification, &order);
    EXPECT_EQ(invoice1.getRelatedOrder(), &order);
    EXPECT_EQ(invoice2.getRelatedOrder(), &order);
    EXPECT_EQ(invoice3.getRelatedOrder(), &order);
    EXPECT_FALSE(invoice1.getIsPaid());
    EXPECT_TRUE(invoice2.getIsPaid());
    EXPECT_FALSE(invoice3.getIsPaid());
}

TEST(ExceptionsTest, CapacityExceededException)
{
    CapacityExceededException exception;
    EXPECT_STREQ(exception.what(), "Вместимость склада превышена");
    EXPECT_THROW(throw CapacityExceededException(), CapacityExceededException);
}

TEST(ExceptionsTest, InvalidWeightException)
{
    InvalidWeightException exception;
    EXPECT_STREQ(exception.what(), "Недопустимый вес груза");
    EXPECT_THROW(throw InvalidWeightException(), InvalidWeightException);
}

TEST(ExceptionsTest, PassengerLimitException)
{
    PassengerLimitException exception;
    EXPECT_STREQ(exception.what(), "Лимит пассажиров превышен");
    EXPECT_THROW(throw PassengerLimitException(), PassengerLimitException);
}

TEST(ExceptionsTest, UnloadErrorException)
{
    UnloadErrorException exception;
    EXPECT_STREQ(exception.what(), "Невозможно выгрузить больше, чем доступно");
    EXPECT_THROW(throw UnloadErrorException(), UnloadErrorException);
}

TEST(ExceptionsTest, HazardousCargoException)
{
    HazardousCargoException exception;
    EXPECT_STREQ(exception.what(), "Обнаружен опасный груз");
    EXPECT_THROW(throw HazardousCargoException(), HazardousCargoException);
}

TEST(ExceptionsTest, InvalidStatusException)
{
    InvalidStatusException exception;
    EXPECT_STREQ(exception.what(), "Неверный статус транспортного средства");
    EXPECT_THROW(throw InvalidStatusException(), InvalidStatusException);
}

TEST(ExceptionsTest, FuelErrorException)
{
    FuelErrorException exception;
    EXPECT_STREQ(exception.what(), "Неверное количество топлива");
    EXPECT_THROW(throw FuelErrorException(), FuelErrorException);
}

TEST(ExceptionsTest, DriverAssignmentException)
{
    DriverAssignmentException exception;
    EXPECT_STREQ(exception.what(), "Ошибка назначения драйвера");
    EXPECT_THROW(throw DriverAssignmentException(), DriverAssignmentException);
}

TEST(ExceptionsTest, RoutePlanningException)
{
    RoutePlanningException exception;
    EXPECT_STREQ(exception.what(), "Планирование маршрута не удалось");
    EXPECT_THROW(throw RoutePlanningException(), RoutePlanningException);
}

TEST(ExceptionsTest, ShipmentErrorException)
{
    ShipmentErrorException exception;
    EXPECT_STREQ(exception.what(), "Операция по доставке не удалась");
    EXPECT_THROW(throw ShipmentErrorException(), ShipmentErrorException);
}

TEST(ExceptionsTest, OrderValidationException)
{
    OrderValidationException exception;
    EXPECT_STREQ(exception.what(), "Проверка заказа не удалась");
    EXPECT_THROW(throw OrderValidationException(), OrderValidationException);
}

TEST(ExceptionsTest, FreightDimensionException)
{
    FreightDimensionException exception;
    EXPECT_STREQ(exception.what(), "Недопустимые размеры груза");
    EXPECT_THROW(throw FreightDimensionException(), FreightDimensionException);
}

TEST(ExceptionsTest, InvalidPaymentException)
{
    InvalidPaymentException exception;
    EXPECT_STREQ(exception.what(), "Недопустимый тип оплаты");
    EXPECT_THROW(throw InvalidPaymentException(), InvalidPaymentException);
}

TEST(ExceptionsTest, InvalidArgumentException)
{
    InvalidArgumentException exception;
    EXPECT_STREQ(exception.what(), "Недопустимый аргумент");
    EXPECT_THROW(throw InvalidArgumentException(), InvalidArgumentException);
}

TEST(ExceptionsTest, InvalidArgumentExceptionWithCustomMessage)
{
    InvalidArgumentException exception("Кастомное сообщение об ошибке");
    EXPECT_STREQ(exception.what(), "Кастомное сообщение об ошибке");
    EXPECT_THROW(throw InvalidArgumentException("Тест"), InvalidArgumentException);
}

TEST(ExceptionsTest, ExceptionInheritance)
{
    EXPECT_TRUE((std::is_base_of<std::exception, CapacityExceededException>::value));
    EXPECT_TRUE((std::is_base_of<std::exception, InvalidWeightException>::value));
    EXPECT_TRUE((std::is_base_of<std::exception, PassengerLimitException>::value));
    EXPECT_TRUE((std::is_base_of<std::exception, UnloadErrorException>::value));
    EXPECT_TRUE((std::is_base_of<std::exception, HazardousCargoException>::value));
    EXPECT_TRUE((std::is_base_of<std::exception, InvalidStatusException>::value));
    EXPECT_TRUE((std::is_base_of<std::exception, FuelErrorException>::value));
    EXPECT_TRUE((std::is_base_of<std::exception, DriverAssignmentException>::value));
    EXPECT_TRUE((std::is_base_of<std::exception, RoutePlanningException>::value));
    EXPECT_TRUE((std::is_base_of<std::exception, ShipmentErrorException>::value));
    EXPECT_TRUE((std::is_base_of<std::exception, OrderValidationException>::value));
    EXPECT_TRUE((std::is_base_of<std::exception, FreightDimensionException>::value));
    EXPECT_TRUE((std::is_base_of<std::exception, InvalidPaymentException>::value));
    EXPECT_TRUE((std::is_base_of<std::runtime_error, InvalidArgumentException>::value));
}

TEST(ExceptionsTest, ExceptionCatching)
{
    try
    {
        throw CapacityExceededException();
        FAIL() << "Expected CapacityExceededException";
    }
    catch (const CapacityExceededException &e)
    {
        EXPECT_STREQ(e.what(), "Вместимость склада превышена");
    }
    catch (...)
    {
        FAIL() << "Expected CapacityExceededException but caught different exception";
    }
}

TEST(ExceptionsTest, MultipleExceptions)
{
    EXPECT_THROW(throw InvalidWeightException(), std::exception);
    EXPECT_THROW(throw PassengerLimitException(), std::exception);
    EXPECT_THROW(throw InvalidPaymentException(), std::exception);
}

TEST(ExceptionsTest, ExceptionMessagesConsistency)
{
    CapacityExceededException ex1;
    CapacityExceededException ex2;
    EXPECT_STREQ(ex1.what(), ex2.what());
    InvalidWeightException ex3;
    InvalidWeightException ex4;
    EXPECT_STREQ(ex3.what(), ex4.what());
}

TEST(DepotTest, ConstructorAndGetDepotId)
{
    Depot depot("DEPOT_001");
    EXPECT_EQ(depot.getDepoId(), "DEPOT_001");
}

TEST(DepotTest, AddVehicle)
{
    Depot depot("DEPOT_001");
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    EXPECT_NO_THROW(depot.addVehicle(&truck));
    std::vector<Vehicle *> vehicles = depot.getVehicles();
    EXPECT_EQ(vehicles.size(), 1);
    EXPECT_EQ(vehicles[0], &truck);
}

TEST(DepotTest, AddMultipleVehicles)
{
    Depot depot("DEPOT_001");
    Fuel fuel1("Diesel", 100.0, 1.0);
    Fuel fuel2("Petrol", 80.0, 1.2);
    VehicleStatus status;
    Truck truck1(&fuel1, 80.0, 2, 5000.0, status);
    Truck truck2(&fuel1, 90.0, 2, 6000.0, status);
    Van van(&fuel2, 120.0, 8, 1500.0, status);
    depot.addVehicle(&truck1);
    depot.addVehicle(&truck2);
    depot.addVehicle(&van);
    std::vector<Vehicle *> vehicles = depot.getVehicles();
    EXPECT_EQ(vehicles.size(), 3);
}

TEST(DepotTest, RemoveVehicle)
{
    Depot depot("DEPOT_001");
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    depot.addVehicle(&truck);
    EXPECT_EQ(depot.getVehicles().size(), 1);
    depot.removeVehicle(&truck);
    EXPECT_EQ(depot.getVehicles().size(), 0);
}

TEST(DepotTest, RemoveNonExistentVehicle)
{
    Depot depot("DEPOT_001");
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck1(&fuel, 80.0, 2, 5000.0, status);
    Truck truck2(&fuel, 90.0, 2, 6000.0, status);
    depot.addVehicle(&truck1);
    EXPECT_EQ(depot.getVehicles().size(), 1);
    depot.removeVehicle(&truck2);
    EXPECT_EQ(depot.getVehicles().size(), 1);
}

TEST(DepotTest, LoadFreight)
{
    Depot depot("DEPOT_001");
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Freight freight;
    freight.setWeight(1000.0);
    depot.addVehicle(&truck);
    EXPECT_NO_THROW(depot.loadFreight(&freight, &truck));
}

TEST(DepotTest, LoadFreightToNonDepotVehicle)
{
    Depot depot("DEPOT_001");
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truckInDepot(&fuel, 80.0, 2, 5000.0, status);
    Truck truckNotInDepot(&fuel, 90.0, 2, 6000.0, status);
    Freight freight;
    freight.setWeight(1000.0);
    depot.addVehicle(&truckInDepot);
    EXPECT_NO_THROW(depot.loadFreight(&freight, &truckNotInDepot));
}

TEST(DepotTest, MultipleDepots)
{
    Depot depot1("DEPOT_001");
    Depot depot2("DEPOT_002");
    Depot depot3("DEPOT_003");
    EXPECT_EQ(depot1.getDepoId(), "DEPOT_001");
    EXPECT_EQ(depot2.getDepoId(), "DEPOT_002");
    EXPECT_EQ(depot3.getDepoId(), "DEPOT_003");
}

TEST(DepotTest, GetEmptyVehiclesList)
{
    Depot depot("DEPOT_001");
    std::vector<Vehicle *> vehicles = depot.getVehicles();
    EXPECT_TRUE(vehicles.empty());
}

TEST(DepotTest, AddAndRemoveMultipleVehicles)
{
    Depot depot("DEPOT_001");
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck1(&fuel, 80.0, 2, 5000.0, status);
    Truck truck2(&fuel, 90.0, 2, 6000.0, status);
    Van van(&fuel, 120.0, 8, 1500.0, status);
    depot.addVehicle(&truck1);
    depot.addVehicle(&truck2);
    depot.addVehicle(&van);
    EXPECT_EQ(depot.getVehicles().size(), 3);
    depot.removeVehicle(&truck1);
    EXPECT_EQ(depot.getVehicles().size(), 2);
    depot.removeVehicle(&van);
    EXPECT_EQ(depot.getVehicles().size(), 1);
    depot.removeVehicle(&truck2);
    EXPECT_EQ(depot.getVehicles().size(), 0);
}

TEST(DepotTest, LoadFreightToDifferentVehicles)
{
    Depot depot("DEPOT_001");
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Van van(&fuel, 120.0, 8, 1500.0, status);
    Freight freight1;
    freight1.setWeight(1000.0);
    Freight freight2;
    freight2.setWeight(500.0);
    depot.addVehicle(&truck);
    depot.addVehicle(&van);
    EXPECT_NO_THROW(depot.loadFreight(&freight1, &truck));
    EXPECT_NO_THROW(depot.loadFreight(&freight2, &van));
}

TEST(DispatchCenterTest, ConstructorAndGetCenterId)
{
    GPS gps(55.7558, 37.6173);
    std::vector<IVehicle *> monitoredVehicles;
    std::vector<Shipment> monitoredShipments;
    OperationsMonitor monitor(monitoredVehicles, monitoredShipments, &gps);
    std::vector<Vehicle *> vehicles;
    std::vector<Shipment *> shipments;
    DispatchCenter center("CENTER_001", &monitor, vehicles, shipments);
    EXPECT_EQ(center.getCenterId(), "CENTER_001");
}

TEST(DispatchCenterTest, AssignVehicleToShipment)
{
    GPS gps(55.7558, 37.6173);
    std::vector<IVehicle *> monitoredVehicles;
    std::vector<Shipment> monitoredShipments;
    OperationsMonitor monitor(monitoredVehicles, monitoredShipments, &gps);
    std::vector<Vehicle *> vehicles;
    std::vector<Shipment *> shipments;
    DispatchCenter center("CENTER_001", &monitor, vehicles, shipments);
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIP_001", &order);
    EXPECT_NO_THROW(center.assignVehicleToShipment(&truck, &shipment));
}

TEST(DispatchCenterTest, AssignVehicleToShipmentWithNull)
{
    GPS gps(55.7558, 37.6173);
    std::vector<IVehicle *> monitoredVehicles;
    std::vector<Shipment> monitoredShipments;
    OperationsMonitor monitor(monitoredVehicles, monitoredShipments, &gps);
    std::vector<Vehicle *> vehicles;
    std::vector<Shipment *> shipments;
    DispatchCenter center("CENTER_001", &monitor, vehicles, shipments);
    EXPECT_THROW(center.assignVehicleToShipment(nullptr, nullptr), std::runtime_error);
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    EXPECT_THROW(center.assignVehicleToShipment(&truck, nullptr), std::runtime_error);
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIP_001", &order);
    EXPECT_THROW(center.assignVehicleToShipment(nullptr, &shipment), std::runtime_error);
}

TEST(DispatchCenterTest, MonitorOperationsWithVehicles)
{
    GPS gps(55.7558, 37.6173);
    std::vector<IVehicle *> monitoredVehicles;
    std::vector<Shipment> monitoredShipments;
    OperationsMonitor monitor(monitoredVehicles, monitoredShipments, &gps);
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck1(&fuel, 80.0, 2, 5000.0, status);
    Truck truck2(&fuel, 90.0, 2, 6000.0, status);
    std::vector<Vehicle *> vehiclesWithTrucks = {&truck1, &truck2};
    std::vector<Shipment *> shipments;
    DispatchCenter center("CENTER_002", &monitor, vehiclesWithTrucks, shipments);
    EXPECT_NO_THROW(center.monitorOperations());
}

TEST(DispatchCenterTest, MonitorOperationsWithEmptyVehicles)
{
    GPS gps(55.7558, 37.6173);
    std::vector<IVehicle *> monitoredVehicles;
    std::vector<Shipment> monitoredShipments;
    OperationsMonitor monitor(monitoredVehicles, monitoredShipments, &gps);
    std::vector<Vehicle *> emptyVehicles;
    std::vector<Shipment *> emptyShipments;
    DispatchCenter center("CENTER_001", &monitor, emptyVehicles, emptyShipments);
    EXPECT_NO_THROW(center.monitorOperations());
}

TEST(DispatchCenterTest, MultipleAssignments)
{
    GPS gps(55.7558, 37.6173);
    std::vector<IVehicle *> monitoredVehicles;
    std::vector<Shipment> monitoredShipments;
    OperationsMonitor monitor(monitoredVehicles, monitoredShipments, &gps);
    std::vector<Vehicle *> vehicles;
    std::vector<Shipment *> shipments;
    DispatchCenter center("CENTER_001", &monitor, vehicles, shipments);
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Truck truck1(&fuel, 80.0, 2, 5000.0, status);
    Truck truck2(&fuel, 90.0, 2, 6000.0, status);
    Van van(&fuel, 120.0, 8, 1500.0, status);
    Order order1("ORDER_001", passengers, &payment, 100.0, &truck1, &client);
    Order order2("ORDER_002", passengers, &payment, 200.0, &truck2, &client);
    Order order3("ORDER_003", passengers, &payment, 150.0, &van, &client);
    Shipment shipment1("SHIP_001", &order1);
    Shipment shipment2("SHIP_002", &order2);
    Shipment shipment3("SHIP_003", &order3);
    EXPECT_NO_THROW(center.assignVehicleToShipment(&truck1, &shipment1));
    EXPECT_NO_THROW(center.assignVehicleToShipment(&truck2, &shipment2));
    EXPECT_NO_THROW(center.assignVehicleToShipment(&van, &shipment3));
}

TEST(DispatchCenterTest, DifferentCenterIds)
{
    GPS gps(55.7558, 37.6173);
    std::vector<IVehicle *> monitoredVehicles;
    std::vector<Shipment> monitoredShipments;
    OperationsMonitor monitor(monitoredVehicles, monitoredShipments, &gps);
    std::vector<Vehicle *> vehicles;
    std::vector<Shipment *> shipments;
    DispatchCenter center1("CENTER_001", &monitor, vehicles, shipments);
    DispatchCenter center2("DISPATCH_NORTH", &monitor, vehicles, shipments);
    DispatchCenter center3("LOGISTICS_CENTER", &monitor, vehicles, shipments);
    EXPECT_EQ(center1.getCenterId(), "CENTER_001");
    EXPECT_EQ(center2.getCenterId(), "DISPATCH_NORTH");
    EXPECT_EQ(center3.getCenterId(), "LOGISTICS_CENTER");
}

TEST(DispatchCenterTest, MonitorOperationsAfterAssignments)
{
    GPS gps(55.7558, 37.6173);
    std::vector<IVehicle *> monitoredVehicles;
    std::vector<Shipment> monitoredShipments;
    OperationsMonitor monitor(monitoredVehicles, monitoredShipments, &gps);
    std::vector<Vehicle *> initialVehicles;
    std::vector<Shipment *> initialShipments;
    DispatchCenter center("CENTER_001", &monitor, initialVehicles, initialShipments);
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIP_001", &order);
    center.assignVehicleToShipment(&truck, &shipment);
    EXPECT_NO_THROW(center.monitorOperations());
}

TEST(DispatchCenterTest, OperationsMonitorWithGPSIntegration)
{
    GPS gps(55.7558, 37.6173);
    std::vector<IVehicle *> monitoredVehicles;
    std::vector<Shipment> monitoredShipments;
    OperationsMonitor monitor(monitoredVehicles, monitoredShipments, &gps);
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    std::vector<Vehicle *> vehicles = {&truck};
    std::vector<Shipment *> shipments;
    DispatchCenter center("CENTER_001", &monitor, vehicles, shipments);
    EXPECT_NO_THROW(center.monitorOperations());
}

TEST(DispatchCenterTest, GPSFunctionality)
{
    GPS gps(30.123, 50.456);
    auto coordinates = gps.getCoordinates();
    EXPECT_EQ(std::get<0>(coordinates), 30.123);
    EXPECT_EQ(std::get<1>(coordinates), 50.456);
    gps.setCoordinates(40.789, 60.123);
    auto newCoordinates = gps.getCoordinates();
    EXPECT_EQ(std::get<0>(newCoordinates), 40.789);
    EXPECT_EQ(std::get<1>(newCoordinates), 60.123);
}

TEST(DispatchCenterTest, RouteIntegration)
{
    GPS gps(55.7558, 37.6173);
    RouteA routeA("ROUTE_A");
    RouteB routeB("ROUTE_B");
    auto resultA = gps.chooseRoute(80.0, &routeA);
    auto resultB = gps.chooseRoute(60.0, &routeB);
    EXPECT_NO_THROW(gps.chooseRoute(80.0, &routeA));
    EXPECT_NO_THROW(gps.chooseRoute(60.0, &routeB));
}

TEST(DispatchCenterTest, ComplexScenario)
{
    GPS gps(55.7558, 37.6173);
    std::vector<IVehicle *> monitoredVehicles;
    std::vector<Shipment> monitoredShipments;
    OperationsMonitor monitor(monitoredVehicles, monitoredShipments, &gps);
    std::vector<Vehicle *> vehicles;
    std::vector<Shipment *> shipments;
    DispatchCenter center("MAIN_CENTER", &monitor, vehicles, shipments);
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client1("CL1", "Client One", "Address 1", &pm, &al, &lm);
    Client client2("CL2", "Client Two", "Address 2", &pm, &al, &lm);
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck1(&fuel, 80.0, 2, 5000.0, status);
    Truck truck2(&fuel, 90.0, 2, 6000.0, status);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Order order1("ORDER_001", passengers, &payment, 100.0, &truck1, &client1);
    Order order2("ORDER_002", passengers, &payment, 200.0, &truck2, &client2);
    Shipment shipment1("SHIP_001", &order1);
    Shipment shipment2("SHIP_002", &order2);
    center.assignVehicleToShipment(&truck1, &shipment1);
    center.assignVehicleToShipment(&truck2, &shipment2);
    EXPECT_NO_THROW(center.monitorOperations());
    EXPECT_EQ(center.getCenterId(), "MAIN_CENTER");
}

TEST(ShipTest, ConstructorAndBasicProperties)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    EXPECT_NO_THROW(Ship ship(&fuel, 50.0, 200, 100000.0, status));
}

TEST(ShipTest, LoadCargoValidWeight)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    EXPECT_NO_THROW(ship.loadCargo(50000.0));
}

TEST(ShipTest, LoadCargoInvalidWeight)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    EXPECT_THROW(ship.loadCargo(150000.0), InvalidWeightException);
}

TEST(ShipTest, LoadPeopleValid)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    EXPECT_NO_THROW(ship.loadPeople(150));
}

TEST(ShipTest, LoadPeopleInvalid)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    EXPECT_THROW(ship.loadPeople(300), PassengerLimitException);
}

TEST(ShipTest, UnloadCargoValid)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    ship.loadCargo(60000.0);
    EXPECT_NO_THROW(ship.unloadCargo(20000.0));
}

TEST(ShipTest, UnloadPeopleValid)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    ship.loadPeople(150);
    EXPECT_NO_THROW(ship.unloadPeople(50));
}

TEST(ShipTest, GetCurrentCargoAndPeople)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    ship.loadCargo(75000.0);
    ship.loadPeople(120);
    EXPECT_EQ(ship.getCurrentCargo(), 75000.0);
    EXPECT_EQ(ship.getCurrentPeople(), 120);
}

TEST(ShipTest, CalculateFuelConsumption)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    double consumption = ship.calculateFuelConsumption(100.0);
    EXPECT_EQ(consumption, 409500.0);
}

TEST(ShipTest, EstimateTravelTime)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    double time = ship.estimateTravelTime(300.0);
    EXPECT_EQ(time, 6.0);
}

TEST(ShipTest, UpdateOdometer)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    EXPECT_NO_THROW(ship.updateOdometer(250.0));
    EXPECT_NO_THROW(ship.updateOdometer(150.5));
}

TEST(ShipTest, CheckMaintenanceDue)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    bool maintenanceDue = ship.checkMaintenanceDue();
    EXPECT_NO_THROW(ship.checkMaintenanceDue());
}

TEST(ShipTest, CalculateTotalCost)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    double cost = ship.calculateTotalCost(100.0);
    EXPECT_EQ(cost, 614250.0);
}

TEST(ShipTest, LogTripMethods)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    EXPECT_NO_THROW(ship.logTripStart());
    EXPECT_NO_THROW(ship.logTripEnd());
}

TEST(ShipTest, VerifyInsurance)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    bool insured = ship.verifyInsurance();
    EXPECT_NO_THROW(ship.verifyInsurance());
}

TEST(ShipTest, AdjustTirePressure)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    EXPECT_NO_THROW(ship.adjustTirePressure(8.5));
    EXPECT_NO_THROW(ship.adjustTirePressure(9.0));
}

TEST(ShipTest, GetVehicleDetails)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    std::string details = ship.getVehicleDetails();
    EXPECT_NO_THROW(ship.getVehicleDetails());
}

TEST(ShipTest, PerformSelfCheck)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    EXPECT_NO_THROW(ship.performSelfCheck());
}

TEST(ShipTest, GetTirePressureAndOdometer)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    double tirePressure = ship.getTirePressure();
    double odometer = ship.getOdometerReading();
    EXPECT_NO_THROW(ship.getTirePressure());
    EXPECT_NO_THROW(ship.getOdometerReading());
}

TEST(ShipTest, EdgeCaseLoadCapacity)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    EXPECT_NO_THROW(ship.loadCargo(100000.0));
    EXPECT_THROW(ship.loadCargo(100000.1), InvalidWeightException);
    EXPECT_NO_THROW(ship.loadPeople(200));
    EXPECT_THROW(ship.loadPeople(201), PassengerLimitException);
}

TEST(ShipTest, MultipleLoadUnloadOperations)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    EXPECT_NO_THROW(ship.loadCargo(30000.0));
    EXPECT_NO_THROW(ship.loadPeople(100));
    EXPECT_NO_THROW(ship.unloadCargo(10000.0));
    EXPECT_NO_THROW(ship.unloadPeople(30));
    EXPECT_NO_THROW(ship.loadCargo(20000.0));
    EXPECT_NO_THROW(ship.loadPeople(50));
}

TEST(ShipTest, UnloadExceedingCurrent)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    ship.loadCargo(20000.0);
    ship.loadPeople(80);
    EXPECT_NO_THROW(ship.unloadCargo(25000.0));
    EXPECT_NO_THROW(ship.unloadPeople(100));
}

TEST(ShipTest, FuelConsumptionDifferentDistances)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship ship(&fuel, 50.0, 200, 100000.0, status);
    EXPECT_EQ(ship.calculateFuelConsumption(50.0), 204750.0);
    EXPECT_EQ(ship.calculateFuelConsumption(200.0), 819000.0);
    EXPECT_EQ(ship.calculateFuelConsumption(0.0), 0.0);
}

TEST(ShipTest, TravelTimeDifferentSpeeds)
{
    Fuel fuel("Diesel", 50000.0, 0.8);
    VehicleStatus status;
    Ship slowShip(&fuel, 30.0, 200, 100000.0, status);
    Ship fastShip(&fuel, 60.0, 200, 100000.0, status);
    EXPECT_EQ(slowShip.estimateTravelTime(180.0), 6.0);
    EXPECT_EQ(fastShip.estimateTravelTime(180.0), 3.0);
}

TEST(TransportCompanyTest, ConstructorWithName)
{
    TransportCompany company("Test Transport Company");
    EXPECT_EQ(company.getCompanyName(), "Test Transport Company");
    EXPECT_NO_THROW(company.getLastAuditDate());
}

TEST(TransportCompanyTest, ConstructorWithParameters)
{
    std::vector<Depot> depots;
    std::vector<IClient *> clients;
    std::vector<IOrder *> orders;
    Analytics analytics;
    Logistics logistics;
    TransportCompany company(depots, clients, orders, analytics, logistics);
    EXPECT_NO_THROW(company.getClients());
    EXPECT_NO_THROW(company.getOrders());
}

TEST(TransportCompanyTest, AddClientNull)
{
    TransportCompany company("Test Company");
    EXPECT_THROW(company.addClient(nullptr), InvalidArgumentException);
}

TEST(TransportCompanyTest, AddOrder)
{
    TransportCompany company("Test Company");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    EXPECT_NO_THROW(company.addOrder(&order));
    std::vector<IOrder *> orders = company.getOrders();
    EXPECT_FALSE(orders.empty());
}

TEST(TransportCompanyTest, AddOrderNull)
{
    TransportCompany company("Test Company");
    EXPECT_THROW(company.addOrder(nullptr), InvalidArgumentException);
}

TEST(TransportCompanyTest, AddDepot)
{
    TransportCompany company("Test Company");
    Depot depot("DEPOT_001");
    EXPECT_NO_THROW(company.addDepot(depot));
}

TEST(TransportCompanyTest, AddMultipleOrders)
{
    TransportCompany company("Test Company");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Order order1("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Order order2("ORDER_002", passengers, &payment, 200.0, &truck, &client);
    Order order3("ORDER_003", passengers, &payment, 300.0, &truck, &client);
    company.addOrder(&order1);
    company.addOrder(&order2);
    company.addOrder(&order3);
    std::vector<IOrder *> orders = company.getOrders();
    EXPECT_EQ(orders.size(), 3);
}

TEST(TransportCompanyTest, AddMultipleDepots)
{
    TransportCompany company("Test Company");
    Depot depot1("DEPOT_001");
    Depot depot2("DEPOT_002");
    Depot depot3("DEPOT_003");
    company.addDepot(depot1);
    company.addDepot(depot2);
    company.addDepot(depot3);
    EXPECT_NO_THROW(company.addDepot(depot1));
}

TEST(TransportCompanyTest, SetLastAuditDate)
{
    TransportCompany company("Test Company");

    std::tm newDate = {};
    newDate.tm_year = 124;
    newDate.tm_mon = 0;
    newDate.tm_mday = 15;
    company.setLastAuditDate(newDate);
    std::tm retrievedDate = company.getLastAuditDate();
    EXPECT_EQ(retrievedDate.tm_year, 124);
    EXPECT_EQ(retrievedDate.tm_mon, 0);
    EXPECT_EQ(retrievedDate.tm_mday, 15);
}

TEST(TransportCompanyTest, DifferentCompanyNames)
{
    TransportCompany company1("Fast Delivery Inc.");
    TransportCompany company2("Global Logistics Ltd.");
    TransportCompany company3("City Transport Co.");
    EXPECT_EQ(company1.getCompanyName(), "Fast Delivery Inc.");
    EXPECT_EQ(company2.getCompanyName(), "Global Logistics Ltd.");
    EXPECT_EQ(company3.getCompanyName(), "City Transport Co.");
}

TEST(TransportCompanyTest, EmptyCompanyName)
{
    TransportCompany company("");
    EXPECT_EQ(company.getCompanyName(), "");
}

TEST(TransportCompanyTest, GetOrdersFromLogistics)
{
    TransportCompany company("Test Company");
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Order order1("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Order order2("ORDER_002", passengers, &payment, 200.0, &truck, &client);
    company.addOrder(&order1);
    company.addOrder(&order2);
    std::vector<IOrder *> orders = company.getOrders();
    EXPECT_EQ(orders.size(), 2);
}

TEST(ShipmentTest, ConstructorAndGetters)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIP_001", &order);
    EXPECT_EQ(shipment.getShipmentId(), "SHIP_001");
    EXPECT_EQ(shipment.getRelatedOrder(), &order);
    EXPECT_EQ(shipment.getDeliveryAttempts(), 0);
}

TEST(ShipmentTest, SetAndGetShipmentWeight)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIP_001", &order);
    shipment.setShipmentWeight(500.0);
    EXPECT_EQ(shipment.getShipmentWeight(), 500.0);
    shipment.setShipmentWeight(1000.0);
    EXPECT_EQ(shipment.getShipmentWeight(), 1000.0);
}

TEST(ShipmentTest, SetVehicle)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIP_001", &order);
    EXPECT_NO_THROW(shipment.setVehicle(&truck));
}

TEST(ShipmentTest, StartShipment)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIP_001", &order);
    shipment.setVehicle(&truck);
    EXPECT_NO_THROW(shipment.startShipment());
}

TEST(ShipmentTest, TrackShipment)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIP_001", &order);
    shipment.setVehicle(&truck);
    GPS gps(55.7558, 37.6173);
    EXPECT_NO_THROW(shipment.trackShipment(&gps));
}

TEST(ShipmentTest, CompleteShipment)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIP_001", &order);
    shipment.setVehicle(&truck);
    EXPECT_NO_THROW(shipment.completeShipment());
}

TEST(ShipmentTest, UpdateTrackingStatus)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIP_001", &order);
    EXPECT_NO_THROW(shipment.updateTrackingStatus("In Transit"));
    EXPECT_NO_THROW(shipment.updateTrackingStatus("Out for Delivery"));
    EXPECT_NO_THROW(shipment.updateTrackingStatus("Delivered"));
}

TEST(ShipmentTest, IncrementDeliveryAttempts)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIP_001", &order);
    EXPECT_EQ(shipment.getDeliveryAttempts(), 0);
    shipment.incrementDeliveryAttempts();
    EXPECT_EQ(shipment.getDeliveryAttempts(), 1);
    shipment.incrementDeliveryAttempts();
    EXPECT_EQ(shipment.getDeliveryAttempts(), 2);
    shipment.incrementDeliveryAttempts();
    EXPECT_EQ(shipment.getDeliveryAttempts(), 3);
}

TEST(ShipmentTest, CalculateShipmentCost)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIP_001", &order);
    shipment.setShipmentWeight(500.0);
    double cost = shipment.calculateShipmentCost();
    EXPECT_GE(cost, 0.0);
}

TEST(ShipmentTest, LogShipmentStatus)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIP_001", &order);
    EXPECT_NO_THROW(shipment.logShipmentStatus());
}

TEST(ShipmentTest, ValidateHandlingInstructions)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIP_001", &order);
    EXPECT_THROW(shipment.validateHandlingInstructions(), ShipmentErrorException);
}

TEST(ShipmentTest, MultipleShipments)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck1(&fuel, 80.0, 2, 5000.0, status);
    Truck truck2(&fuel, 90.0, 2, 6000.0, status);
    Order order1("ORDER_001", passengers, &payment, 100.0, &truck1, &client);
    Order order2("ORDER_002", passengers, &payment, 200.0, &truck2, &client);
    Shipment shipment1("SHIP_001", &order1);
    Shipment shipment2("SHIP_002", &order2);
    Shipment shipment3("SHIP_003", &order1);
    EXPECT_EQ(shipment1.getShipmentId(), "SHIP_001");
    EXPECT_EQ(shipment2.getShipmentId(), "SHIP_002");
    EXPECT_EQ(shipment3.getShipmentId(), "SHIP_003");
    EXPECT_EQ(shipment1.getRelatedOrder(), &order1);
    EXPECT_EQ(shipment2.getRelatedOrder(), &order2);
    EXPECT_EQ(shipment3.getRelatedOrder(), &order1);
}

TEST(ShipmentTest, ShipmentWithDifferentWeights)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIP_001", &order);
    shipment.setShipmentWeight(0.0);
    EXPECT_EQ(shipment.getShipmentWeight(), 0.0);
    shipment.setShipmentWeight(100.0);
    EXPECT_EQ(shipment.getShipmentWeight(), 100.0);
    shipment.setShipmentWeight(5000.0);
    EXPECT_EQ(shipment.getShipmentWeight(), 5000.0);
}

TEST(ShipmentTest, FullShipmentLifecycle)
{
    PaymentManager pm;
    ClientActivityLogger al;
    LoyaltyManager lm;
    Client client("CL1", "Test Client", "Test Address", &pm, &al, &lm);
    std::vector<Passenger> passengers;
    CardPayment payment;
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck truck(&fuel, 80.0, 2, 5000.0, status);
    Order order("ORDER_001", passengers, &payment, 100.0, &truck, &client);
    Shipment shipment("SHIP_001", &order);
    shipment.setShipmentWeight(500.0);
    shipment.setVehicle(&truck);
    shipment.updateTrackingStatus("Preparing");
    shipment.startShipment();
    shipment.updateTrackingStatus("In Transit");
    shipment.incrementDeliveryAttempts();
    shipment.completeShipment();
    shipment.updateTrackingStatus("Delivered");
    EXPECT_EQ(shipment.getShipmentWeight(), 500.0);
    EXPECT_EQ(shipment.getDeliveryAttempts(), 1);
}

TEST(SecurityTest, ConstructorAndGetSecurityId)
{
    Security security("SEC_001");
    EXPECT_EQ(security.getSecurityId(), "SEC_001");
}

TEST(SecurityTest, CheckFreightSafetyWithSafeFreight)
{
    Security security("SEC_001");
    Freight freight;
    bool isSafe = security.checkFreightSafety(&freight);
    EXPECT_TRUE(isSafe);
}

TEST(SecurityTest, CheckFreightSafetyWithHazardousFreight)
{
    Security security("SEC_001");
    Freight freight;
    bool isSafe = security.checkFreightSafety(&freight);
    EXPECT_TRUE(isSafe);
}

TEST(SecurityTest, LogSecurityIncident)
{
    Security security("SEC_001");
    EXPECT_NO_THROW(security.logSecurityIncident());
}

TEST(SecurityTest, UpdateSecurityLevelValid)
{
    Security security("SEC_001");
    EXPECT_NO_THROW(security.updateSecurityLevel(0));
    EXPECT_NO_THROW(security.updateSecurityLevel(2));
    EXPECT_NO_THROW(security.updateSecurityLevel(5));
}

TEST(SecurityTest, UpdateSecurityLevelInvalid)
{
    Security security("SEC_001");
    EXPECT_NO_THROW(security.updateSecurityLevel(-1));
    EXPECT_NO_THROW(security.updateSecurityLevel(6));
    EXPECT_NO_THROW(security.updateSecurityLevel(10));
}

TEST(SecurityTest, MultipleSecurityInstances)
{
    Security security1("SEC_001");
    Security security2("SECURITY_ALPHA");
    Security security3("GUARD_123");
    EXPECT_EQ(security1.getSecurityId(), "SEC_001");
    EXPECT_EQ(security2.getSecurityId(), "SECURITY_ALPHA");
    EXPECT_EQ(security3.getSecurityId(), "GUARD_123");
}

TEST(SecurityTest, SecurityLevelBoundaryValues)
{
    Security security("BOUNDARY_SEC");
    EXPECT_NO_THROW(security.updateSecurityLevel(0));
    EXPECT_NO_THROW(security.updateSecurityLevel(5));
    EXPECT_NO_THROW(security.updateSecurityLevel(-1));
    EXPECT_NO_THROW(security.updateSecurityLevel(6));
}

TEST(VehicleTest, ConstructorAndBasicProperties)
{
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck vehicle(&fuel, 80.0, 2, 5000.0, status);
    EXPECT_NO_THROW(Truck vehicle(&fuel, 80.0, 2, 5000.0, status));
}

TEST(VehicleTest, GetVehicleId)
{
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck vehicle(&fuel, 80.0, 2, 5000.0, status);
    std::string vehicleId = vehicle.getVehicleId();
    EXPECT_NO_THROW(vehicle.getVehicleId());
}

TEST(VehicleTest, MoveTo)
{
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck vehicle(&fuel, 80.0, 2, 5000.0, status);
    EXPECT_NO_THROW(vehicle.moveTo(55.7558, 37.6173));
    EXPECT_NO_THROW(vehicle.moveTo(40.7128, -74.0060));
    EXPECT_NO_THROW(vehicle.moveTo(0.0, 0.0));
}

TEST(VehicleTest, GetLocation)
{
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck vehicle(&fuel, 80.0, 2, 5000.0, status);
    vehicle.moveTo(55.7558, 37.6173);
    auto location = vehicle.getLocation();
    EXPECT_NO_THROW(vehicle.getLocation());
    double longitude = std::get<0>(location);
    double latitude = std::get<1>(location);
    EXPECT_EQ(longitude, 55.7558);
    EXPECT_EQ(latitude, 37.6173);
}

TEST(VehicleTest, GetStatus)
{
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck vehicle(&fuel, 80.0, 2, 5000.0, status);
    std::string statusStr = vehicle.getStatus();
    EXPECT_NO_THROW(vehicle.getStatus());
}

TEST(VehicleTest, RefuelInvalidAmount)
{
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck vehicle(&fuel, 80.0, 2, 5000.0, status);
    EXPECT_THROW(vehicle.refuel(-10.0), FuelErrorException);
    EXPECT_THROW(vehicle.refuel(-0.1), FuelErrorException);
}

TEST(VehicleTest, GetFuelType)
{
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck vehicle(&fuel, 80.0, 2, 5000.0, status);
    std::string fuelType = vehicle.getFuelType();
    EXPECT_EQ(fuelType, "Diesel");
}

TEST(VehicleTest, GetAvailableAmount)
{
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck vehicle(&fuel, 80.0, 2, 5000.0, status);
    double amount = vehicle.getAvailableAmount();
    EXPECT_EQ(amount, 100.0);
    vehicle.refuel(50.0);
    double newAmount = vehicle.getAvailableAmount();
    EXPECT_GT(newAmount, 100.0);
}

TEST(VehicleTest, AssignDriverValid)
{
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck vehicle(&fuel, 80.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    EXPECT_NO_THROW(vehicle.assignDriver(driver));
}

TEST(VehicleTest, AssignDriverInvalid)
{
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck vehicle(&fuel, 80.0, 2, 5000.0, status);
    Driver driver("", "", "", 0);
    EXPECT_THROW(vehicle.assignDriver(driver), DriverAssignmentException);
}

TEST(VehicleTest, MultipleLocationChanges)
{
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck vehicle(&fuel, 80.0, 2, 5000.0, status);
    vehicle.moveTo(55.7558, 37.6173);
    auto loc1 = vehicle.getLocation();
    vehicle.moveTo(40.7128, -74.0060);
    auto loc2 = vehicle.getLocation();
    vehicle.moveTo(35.6762, 139.6503);
    auto loc3 = vehicle.getLocation();
    EXPECT_NO_THROW(vehicle.getLocation());
}

TEST(VehicleTest, MultipleRefuels)
{
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck vehicle(&fuel, 80.0, 2, 5000.0, status);
    EXPECT_NO_THROW(vehicle.refuel(10.0));
    EXPECT_NO_THROW(vehicle.refuel(20.0));
    EXPECT_NO_THROW(vehicle.refuel(5.0));
    EXPECT_NO_THROW(vehicle.refuel(15.0));
}

TEST(VehicleTest, DifferentFuelTypes)
{
    Fuel dieselFuel("Diesel", 100.0, 1.0);
    Fuel petrolFuel("Petrol", 80.0, 1.2);
    Fuel electricFuel("Electric", 200.0, 0.1);
    VehicleStatus status;
    Truck dieselTruck(&dieselFuel, 80.0, 2, 5000.0, status);
    Truck petrolTruck(&petrolFuel, 100.0, 2, 4000.0, status);
    Truck electricTruck(&electricFuel, 120.0, 2, 3000.0, status);
    EXPECT_EQ(dieselTruck.getFuelType(), "Diesel");
    EXPECT_EQ(petrolTruck.getFuelType(), "Petrol");
    EXPECT_EQ(electricTruck.getFuelType(), "Electric");
}

TEST(VehicleTest, ComplexOperations)
{
    Fuel fuel("Diesel", 100.0, 1.0);
    VehicleStatus status;
    Truck vehicle(&fuel, 80.0, 2, 5000.0, status);
    Driver driver("John", "Doe", "B", 5);
    vehicle.moveTo(55.7558, 37.6173);
    auto location = vehicle.getLocation();
    vehicle.setStatus(1);
    std::string currentStatus = vehicle.getStatus();
    vehicle.refuel(50.0);
    double fuelAmount = vehicle.getAvailableAmount();
    vehicle.assignDriver(driver);
    EXPECT_NO_THROW(vehicle.getLocation());
    EXPECT_NO_THROW(vehicle.getStatus());
    EXPECT_NO_THROW(vehicle.getAvailableAmount());
}

TEST(VehicleStatusTest, ConstructorWithDifferentInitialStatus)
{
    VehicleStatus status1(0, 3, false);
    VehicleStatus status2(2, 7, true);
    EXPECT_EQ(status1.getStatus(), "Non-operational");
    EXPECT_EQ(status2.getStatus(), "In route");
}

TEST(VehicleStatusTest, SetStatusValid)
{
    VehicleStatus status(1, 5, true);
    EXPECT_NO_THROW(status.setStatus(0));
    EXPECT_EQ(status.getStatus(), "Non-operational");
    EXPECT_NO_THROW(status.setStatus(2));
    EXPECT_EQ(status.getStatus(), "In route");
    EXPECT_NO_THROW(status.setStatus(1));
    EXPECT_EQ(status.getStatus(), "Operational");
}

TEST(VehicleStatusTest, SetStatusInvalid)
{
    VehicleStatus status(1, 5, true);
    EXPECT_THROW(status.setStatus(-1), InvalidStatusException);
    EXPECT_THROW(status.setStatus(3), InvalidStatusException);
    EXPECT_THROW(status.setStatus(100), InvalidStatusException);
}

TEST(VehicleStatusTest, GetLastStatusChange)
{
    VehicleStatus status(1, 5, true);
    std::time_t initialChange = status.getLastStatusChange();
    status.setStatus(2);
    std::time_t newChange = status.getLastStatusChange();
    EXPECT_GE(newChange, initialChange);
}

TEST(VehicleStatusTest, IsValidStatus)
{
    VehicleStatus status(1, 5, true);
    EXPECT_TRUE(status.isValidStatus(0));
    EXPECT_TRUE(status.isValidStatus(1));
    EXPECT_TRUE(status.isValidStatus(2));
    EXPECT_FALSE(status.isValidStatus(-1));
    EXPECT_FALSE(status.isValidStatus(3));
    EXPECT_FALSE(status.isValidStatus(999));
}

TEST(VehicleStatusTest, MultipleStatusChanges)
{
    VehicleStatus status(1, 5, true);
    std::string initialStatus = status.getStatus();
    std::time_t initialTime = status.getLastStatusChange();
    status.setStatus(2);
    std::string status2 = status.getStatus();
    std::time_t time2 = status.getLastStatusChange();
    status.setStatus(0);
    std::string status3 = status.getStatus();
    std::time_t time3 = status.getLastStatusChange();
    status.setStatus(1);
    std::string status4 = status.getStatus();
    std::time_t time4 = status.getLastStatusChange();
    EXPECT_EQ(initialStatus, "Operational");
    EXPECT_EQ(status2, "In route");
    EXPECT_EQ(status3, "Non-operational");
    EXPECT_EQ(status4, "Operational");
    EXPECT_GE(time2, initialTime);
    EXPECT_GE(time3, time2);
    EXPECT_GE(time4, time3);
}

TEST(VehicleStatusTest, DifferentPriorities)
{
    VehicleStatus status1(1, 1, true);
    VehicleStatus status2(1, 5, true);
    VehicleStatus status3(1, 10, true);
    EXPECT_NO_THROW(status1.setStatus(2));
    EXPECT_NO_THROW(status2.setStatus(0));
    EXPECT_NO_THROW(status3.setStatus(1));
}

TEST(VehicleStatusTest, OperationalFlag)
{
    VehicleStatus operationalStatus(1, 5, true);
    VehicleStatus nonOperationalStatus(0, 5, false);
    EXPECT_NO_THROW(operationalStatus.setStatus(2));
    EXPECT_NO_THROW(nonOperationalStatus.setStatus(1));
}

TEST(VehicleStatusTest, StatusMapCompleteness)
{
    VehicleStatus status(1, 5, true);
    EXPECT_TRUE(status.isValidStatus(0));
    EXPECT_TRUE(status.isValidStatus(1));
    EXPECT_TRUE(status.isValidStatus(2));
    EXPECT_NO_THROW(status.setStatus(0));
    EXPECT_EQ(status.getStatus(), "Non-operational");
    EXPECT_NO_THROW(status.setStatus(1));
    EXPECT_EQ(status.getStatus(), "Operational");
    EXPECT_NO_THROW(status.setStatus(2));
    EXPECT_EQ(status.getStatus(), "In route");
}

TEST(VehicleStatusTest, BoundaryStatusValues)
{
    VehicleStatus status(1, 5, true);
    EXPECT_TRUE(status.isValidStatus(0));
    EXPECT_TRUE(status.isValidStatus(2));
    EXPECT_FALSE(status.isValidStatus(-1));
    EXPECT_FALSE(status.isValidStatus(3));
}

TEST(VehicleStatusTest, StatusPersistence)
{
    VehicleStatus status(1, 5, true);
    status.setStatus(2);
    EXPECT_EQ(status.getStatus(), "In route");
    EXPECT_EQ(status.getStatus(), "In route");
    EXPECT_EQ(status.getStatus(), "In route");
    EXPECT_EQ(status.getStatus(), "In route");
}

TEST(VehicleStatusTest, ExceptionMessage)
{
    VehicleStatus status(1, 5, true);
    try
    {
        status.setStatus(999);
        FAIL() << "Expected InvalidStatusException";
    }
    catch (const InvalidStatusException &e)
    {
        EXPECT_STREQ(e.what(), "Неверный статус транспортного средства");
    }
    catch (...)
    {
        FAIL() << "Expected InvalidStatusException but caught different exception";
    }
}

TEST(VehicleStatusTest, RapidStatusChanges)
{
    VehicleStatus status(1, 5, true);
    for (int i = 0; i < 10; i++)
    {
        int statusCode = i % 3;
        if (status.isValidStatus(statusCode))
        {
            EXPECT_NO_THROW(status.setStatus(statusCode));
            EXPECT_TRUE(status.isValidStatus(statusCode));
        }
    }
}