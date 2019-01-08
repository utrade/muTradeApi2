#ifndef BRACKETORDERPARAMS_H
#define BRACKETORDERPARAMS_H

#include "ui_bracketordergui.h"
#include "../../FrontEnd_Api_Includes/dll_includes/sharedParams.h"

class BracketOrderParams
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

    API2::PARAM * _orderTypeLeg1;
    API2::PARAM * _fillTypeLeg1;
    API2::PARAM * _quantityLeg1;
    API2::PARAM * _limitPriceLeg1;
    API2::PARAM * _triggerPriceLeg1;
    API2::PARAM * _orderTypeLeg2;
    API2::PARAM * _fillTypeLeg2;
    API2::PARAM * _quantityLeg2;
    API2::PARAM * _limitPriceLeg2;
    API2::PARAM * _triggerPriceLeg2;
    API2::PARAM * _orderTypeLeg3;
    API2::PARAM * _fillTypeLeg3;
    API2::PARAM * _quantityLeg3;
    API2::PARAM * _limitPriceLeg3;
    API2::PARAM * _triggerPriceLeg3;

    BracketOrderParams(Ui::BracketOrderGui *ui);
    ~BracketOrderParams();
    void makeParamsList();
    void addParams(API2::PARAM *param, int colomnIndex=-1,short filtherWidget=API2::WidgetType_MAX,bool isEditable=false);
    API2::StrategyParamMap &getParamList() {return _paramsMap;}
};

#endif // BRACKETORDERPARAMS_H
