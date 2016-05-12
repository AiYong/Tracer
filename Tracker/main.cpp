#include "LoginWidget.h"
#include <QApplication>
#include "BrokerManager.h"
#include "AccountManager.h"
#include <QString>
#include "AccountResourceManager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //LoginWidget w;
    //w.show();
    QStringList MarketUrls;
    MarketUrls << QString("tcp://180.168.212.76:31213");
    QStringList TradeUrls;
    //TradeUrls << QString("tcp://27.115.78.155:41205");
	TradeUrls << QString("tcp://27.115.78.154:31205");
    QString strName("HaiTong");
    QString strID("8000");
    QString strPlatform("CTP");
	Broker *pBroker = BrokerManager::GetInstance()->GetBroker(strID);
	if(pBroker)
	{
		BrokerManager::GetInstance()->Remove(pBroker);
	}
	pBroker = BrokerManager::GetInstance()->Create(strName, strID, TradeUrls, MarketUrls, strPlatform);
    //Account *pAccount = AccountManager::GetInstance()->CreateAccount("180009","AIYONG","789211",pBroker);
	Account *pAccount = AccountManager::GetInstance()->CreateAccount("41000454", "AIYONG", "158963", pBroker);
	std::shared_ptr<AccountInfo> pAccountInfo = AccountResourceManager::GetInstance()->GetAccountInfo(pAccount);
    return 0;
}
