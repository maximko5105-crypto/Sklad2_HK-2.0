cmake_minimum_required(VERSION 3.16)

project(sklad2_HK VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Sql
    PrintSupport
    Charts
)

qt_standard_project_setup()

set(SRC ${CMAKE_CURRENT_SOURCE_DIR})

# ================== SOURCES ==================

set(PROJECT_SOURCES
    ${SRC}/main.cpp

    # Core
    ${SRC}/core/Session.cpp
    ${SRC}/core/Logger.cpp

    # Database
    ${SRC}/database/DatabaseService.cpp

    # Services
    ${SRC}/services/AuthService.cpp
    ${SRC}/services/ContainerService.cpp
    ${SRC}/services/HistoryService.cpp
    ${SRC}/services/NotificationService.cpp
    ${SRC}/services/OrderService.cpp
    ${SRC}/services/ProductService.cpp
    ${SRC}/services/QRService.cpp
    ${SRC}/services/ReportService.cpp
    ${SRC}/services/RequestService.cpp
    ${SRC}/services/StockService.cpp
    ${SRC}/services/UserService.cpp

    # UI core
    ${SRC}/UI/MainWindow.cpp
    ${SRC}/UI/AuthWindow.cpp
    ${SRC}/UI/LoginDialog.cpp
    ${SRC}/UI/core/SplashScreen.cpp

    # UI components
    ${SRC}/UI/components/KPIWidget.cpp

    # UI pages
    ${SRC}/UI/pages/DashboardPage.cpp
    ${SRC}/UI/pages/RequestsPage.cpp
    ${SRC}/UI/pages/OrdersPage.cpp
    ${SRC}/UI/pages/WarehousePage.cpp
    ${SRC}/UI/pages/AnalyticsPage.cpp
    ${SRC}/UI/pages/ReportsPage.cpp
    ${SRC}/UI/pages/SettingsPage.cpp

    # Utils
    ${SRC}/utils/QrGenerator.cpp
)

# ================== HEADERS ==================

set(PROJECT_HEADERS
    ${SRC}/core/Session.h
    ${SRC}/core/Logger.h
    ${SRC}/core/Statuses.h

    ${SRC}/database/DatabaseService.h

    ${SRC}/domain/Roles.h

    ${SRC}/services/AuthService.h
    ${SRC}/services/ContainerService.h
    ${SRC}/services/HistoryService.h
    ${SRC}/services/NotificationService.h
    ${SRC}/services/OrderService.h
    ${SRC}/services/ProductService.h
    ${SRC}/services/QRService.h
    ${SRC}/services/ReportService.h
    ${SRC}/services/RequestService.h
    ${SRC}/services/StockService.h
    ${SRC}/services/UserService.h

    ${SRC}/UI/MainWindow.h
    ${SRC}/UI/AuthWindow.h
    ${SRC}/UI/LoginDialog.h
    ${SRC}/UI/core/SplashScreen.h
    ${SRC}/UI/components/KPIWidget.h

    ${SRC}/UI/pages/DashboardPage.h
    ${SRC}/UI/pages/RequestsPage.h
    ${SRC}/UI/pages/OrdersPage.h
    ${SRC}/UI/pages/WarehousePage.h
    ${SRC}/UI/pages/AnalyticsPage.h
    ${SRC}/UI/pages/ReportsPage.h
    ${SRC}/UI/pages/SettingsPage.h

    ${SRC}/utils/QrGenerator.h
)

qt_add_executable(sklad2_HK
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
)

target_link_libraries(sklad2_HK PRIVATE
    Qt6::Widgets
    Qt6::Sql
    Qt6::PrintSupport
    Qt6::Charts
)

target_include_directories(sklad2_HK PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)


if (WIN32)
    set_target_properties(sklad2_HK PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()
