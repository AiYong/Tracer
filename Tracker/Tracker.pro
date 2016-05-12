#-------------------------------------------------
#
# Project created by QtCreator 2016-03-27T13:09:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

TARGET = Tracker
TEMPLATE = app

INCLUDEPATH +=.
LIBS += ..\Libs\thosttraderapi.lib
LIBS += ..\Libs\thostmduserapi.lib

SOURCES += main.cpp\
        LoginWidget.cpp \
    MainWidget.cpp \
    AccountManageWidget.cpp \
    AccountTracker.cpp \
    Account.cpp \
    AccountManager.cpp \
    MarketData.cpp \
    Instrument.cpp \
    Platform.cpp \
    MarketDataSubscriber.cpp \
    Position.cpp \
    PlatformFactory.cpp \
    CTPPlatform.cpp \
    Order.cpp \
    Broker.cpp \
    BrokerManager.cpp \
    MarketDataListener.cpp \
    PositionCost.cpp \
    DatabaseManager.cpp \
    Transaction.cpp \
    AccountTrackWidget.cpp \
    CTPMarketDataSubscriber.cpp \
    OrderOperator.cpp \
    AccountResouceManager.cpp \
    CTPOrderSubscriber.cpp \
    OrderSubscriber.cpp \
    CTPOrderProcessor.cpp \
    OrderProcessor.cpp \
    AccountTrackerData.cpp \
    AccountTrackerPosition.cpp \
    AccountTrackerTradeProcessor.cpp \
    AccountTrackerEventProcessor.cpp \
    AccountTrackerSetting.cpp \
    AccountTradeInfo.cpp \
    TradeService.cpp \
    CTPAccountInfoQuerier.cpp

HEADERS  += LoginWidget.h \
    MainWidget.h \
    AccountManageWidget.h \
    Account.h \
    AccountManager.h \
    AccountTracker.h \
    MarketData.h \
    Instrument.h \
    Platform.h \
    MarketDataSubscriber.h \
    Position.h \
    PlatformFactory.h \
    CTPPlatform.h \
    Direction.h \
    HedgeFlag.h \
    Operation.h \
    PriceMode.h \
    Order.h \
    Transaction.h \
    OrderProcessor.h \
    OrderListener.h \
    Broker.h \
    BrokerManager.h \
    MarketDataListener.h \
    PositionCost.h \
    ObjectPersister.h \
    ObjectPersistManager.h \
    DatabaseManager.h \
    CTPOrderProcessor.h \
    CTPMarketDataSubscriber.h \
    OrderOperator.h \
    OrderPersister.h \
    PositionPersister.h \
    PositionCostPersister.h \
    AccountResourceManager.h \
    BrokerPersister.h \
    TransactionPersister.h \
    InstrumentPersister.h \
    AccountPersister.h \
    OrderSubscriber.h \
    CTPOrderSubscriber.h \
    OrderStatus.h \
    AccountTrackerEventProcessor.h \
    AccountTrackerWidget.h \
    AccountTrackerData.h \
    AccountTrackerPosition.h \
    AccountTrackerTradeProcessor.h \
    AccountTrackerSetting.h \
    OrderError.h \
    AccountTrackerSettingPersister.h \
    AccountTrackerPositionPersister.h \
    AccountTradeInfo.h \
    TradeService.h \
    CTPAccountInfoQuerier.h
