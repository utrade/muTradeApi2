#ifndef SNIPERPARAMS_H
#define SNIPERPARAMS_H
#include "ui_sniperdialog.h"
#include "F:/GUIR/gui/FrontEnd_Api_Includes/dll_includes/sharedParams.h"

class Sniperparams
{
public:
    API2::StrategyParamMap _paramsMap;

    API2::PARAM * _transactionType;
    API2::PARAM * _clientId;
    API2::PARAM * _strategyId;
    API2::PARAM * _adminTokenId;
    API2::PARAM * _state;
    API2::PARAM * _strategyComment;
    API2::PARAM * _riskStatus;
    API2::PARAM * _portfolioId;
    API2::PARAM * _sequenceNumber;
    API2::PARAM * _oldStrategyId;
    API2::PARAM * _symbolId;
    API2::PARAM * _symbolName;
    API2::PARAM * _mode;
    API2::PARAM * _quantity;
    API2::PARAM * _triggerprice;
    API2::PARAM * _limitprice;
    API2::PARAM * _accountDetailLeg;
    API2::PARAM * _orderType;
    Sniperparams(Ui::Sniperdialog *ui);
    ~Sniperparams();
    void makeParamList();
    void addParams(API2::PARAM *param,int columnIndex=-1,short filterWidget=API2::WidgetType_MAX, bool isEditable=false);
    API2::StrategyParamMap &getParamList() {return _paramsMap;}
};

#endif // SNIPERPARAMS_H
