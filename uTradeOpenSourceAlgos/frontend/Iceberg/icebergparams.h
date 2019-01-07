#ifndef ICEBERGPARAMS_H
#define ICEBERGPARAMS_H

#include "ui_icebergui.h"
#include "../../FrontEnd_Api_Includes/dll_includes/sharedParams.h"

class icebergparams
{
    API2::StrategyParamMap _paramsMap;

public:
    icebergparams(Ui::Icebergui *ui);
    
    API2::PARAM *  _strategyVersion;
    API2::PARAM *  _transactionType;
    API2::PARAM *  _clientId;
    API2::PARAM *  _strategyId;
    API2::PARAM *  _symbolName;
    API2::PARAM *  _sequenceNumber;
    API2::PARAM *  _adminTokenId;
    API2::PARAM *  _state;
    API2::PARAM *  _strategyComment;
    API2::PARAM *  _riskStatus;
    API2::PARAM *  _portfolioId;
    API2::PARAM *  _oldStrategyId;
    API2::PARAM *  _orderType;
    API2::PARAM *  _limitPrice;
    API2::PARAM *  _totalQuantity;
    API2::PARAM *  _orderMode;
    API2::PARAM *  _symbolIdOne;
    API2::PARAM *  _strategyLeg;
    API2::PARAM *  _tradedQtyLegOne;
    API2::PARAM *  _remQty;
    API2::PARAM *  _SIDTotalQty;
    API2::PARAM *  _disclosedQuantity;
    API2::PARAM *  _disclosedQtyPercent;
    API2::PARAM *  _fillType;

    short _portfolioIndex;
    ~icebergparams();

    void makeParamList();
    void addParams(API2::PARAM *param,
                   int columnIndex=-1,
                   short filterWidget=API2::WidgetType_MAX,
                   bool isEditable=false,
                   short sortingType=API2::SortingType_MAX);
    API2::StrategyParamMap &getParamList()
    {
        return _paramsMap;
    }
};

#endif // ICEBERGPARAMS_H
