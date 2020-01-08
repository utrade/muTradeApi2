#ifndef FUTFUTPARAMS_H
#define FUTFUTPARAMS_H

#include "ui_uilibrary.h"
#include "../includes/dll_includes/sharedParams.h"

class FutFutParams
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
    API2::PARAM * _symbolId;
    API2::PARAM * _symbolName;
    API2::PARAM * _mode;
    API2::PARAM * _symbolId2;
    API2::PARAM * _symbolName2;
    API2::PARAM * _mode2;
    API2::PARAM * _totalLots;
    API2::PARAM * _orderLots;

    API2::PARAM * _desiredSpread;
    API2::PARAM * _hedgeMethod;
    API2::PARAM * _marketPercentage;
    API2::PARAM * _isTbt;
    API2::PARAM * _currentSpread;
    FutFutParams(Ui::UiLibrary *ui);
    ~FutFutParams();
    void makeParamList();
    void addParams(API2::PARAM *param,int columnIndex=-1,short filterWidget=API2::WidgetType_MAX, bool isEditable=false);
    API2::StrategyParamMap &getParamList() {return _paramsMap;}
};

#endif
