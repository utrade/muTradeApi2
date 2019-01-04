#include "icebergparams.h"
#include <iostream>

icebergparams::icebergparams(Ui::Icebergui *ui):_portfolioIndex(0)
{
    _strategyVersion = new API2::PARAM("strategyVersion",
                                       "",
                                       NULL,
                                       API2::UI_ELEMENT_NO_UI,
                                       API2::DATA_TYPE_UNSIGNED_LONG,
                                       API2::UI_STATE_DISABLED,
                                       API2::TABLE_STATE_HIDE,
                                       API2::DB_FEILD_HIDE);
    _transactionType = new API2::PARAM("transactionType",
                                       "",
                                       NULL,
                                       API2::UI_ELEMENT_NO_UI,
                                       API2::DATA_TYPE_CHARACTER,
                                       API2::UI_STATE_DISABLED,
                                       API2::TABLE_STATE_HIDE,
                                       API2::DB_FEILD_SHOW);
    _clientId        = new API2::PARAM("clientId",
                                       "C_ID",
                                       NULL,
                                       API2::UI_ELEMENT_NO_UI ,
                                       API2::DATA_TYPE_INTEGER ,
                                       API2::UI_STATE_DISABLED ,
                                       API2::TABLE_STATE_HIDE ,
                                       API2::DB_FEILD_SHOW);
    _strategyId      = new API2::PARAM("strategyId",
                                       "S_ID",
                                       NULL,
                                       API2::UI_ELEMENT_NO_UI,
                                       API2::DATA_TYPE_INTEGER,
                                       API2::UI_STATE_ENABLED,
                                       API2::TABLE_STATE_SHOW,
                                       API2::DB_FEILD_SHOW);
    _sequenceNumber  = new API2::PARAM("sequenceNumber",
                                       "",
                                       NULL,
                                       API2::UI_ELEMENT_NO_UI,
                                       API2::DATA_TYPE_INTEGER,
                                       API2::UI_STATE_DISABLED ,
                                       API2::TABLE_STATE_HIDE ,
                                       API2::DB_FEILD_SHOW);
    _adminTokenId    = new API2::PARAM("adminTokenId",
                                       "Token_Id",
                                       NULL,
                                       API2::UI_ELEMENT_NO_UI,
                                       API2::DATA_TYPE_UNSIGNED_LONG,
                                       API2::UI_STATE_DISABLED,
                                       API2::TABLE_STATE_SHOW,
                                       API2::DB_FEILD_SHOW);
    _state           = new API2::PARAM("state",
                                       "STATE",
                                       NULL,
                                       API2::UI_ELEMENT_NO_UI ,
                                       API2::DATA_TYPE_INTEGER ,
                                       API2::UI_STATE_ENABLED ,
                                       API2::TABLE_STATE_SHOW ,
                                       API2::DB_FEILD_SHOW);
    _strategyComment = new API2::PARAM("strategyComment",
                                       "COMMENT",
                                       NULL,
                                       API2::UI_ELEMENT_NO_UI,
                                       API2::DATA_TYPE_STRING ,
                                       API2::UI_STATE_DISABLED ,
                                       API2::TABLE_STATE_SHOW ,
                                       API2::DB_FEILD_SHOW);
    _riskStatus      = new API2::PARAM("riskStatus",
                                       "RISK_STATUS",
                                       NULL,
                                       API2::UI_ELEMENT_NO_UI,
                                       API2::DATA_TYPE_SHORT,
                                       API2::UI_STATE_DISABLED,
                                       API2::TABLE_STATE_HIDE,
                                       API2::DB_FEILD_SHOW);
    _portfolioId     = new API2::PARAM("portfolioId",
                                       "P_ID",
                                       NULL,
                                       API2::UI_ELEMENT_NO_UI,
                                       API2::DATA_TYPE_UNSIGNED_LONG,
                                       API2::UI_STATE_DISABLED,
                                       API2::TABLE_STATE_SHOW,
                                       API2::DB_FEILD_SHOW,
                                       API2::UPDATE_STATE_DISABLE);
    _oldStrategyId   = new API2::PARAM("oldStrategyId",
                                       "OLD_S_ID",
                                       NULL,
                                       API2::UI_ELEMENT_NO_UI,
                                       API2::DATA_TYPE_INTEGER,
                                       API2::UI_STATE_DISABLED,
                                       API2::TABLE_STATE_HIDE,
                                       API2::DB_FEILD_SHOW);
    _symbolIdOne     = new API2::PARAM("symbolidFirstLeg",
                                       "SymbolIdLeg1",
                                       NULL,
                                       API2::UI_ELEMENT_NO_UI ,
                                       API2::DATA_TYPE_UNSIGNED_LONG ,
                                       API2::UI_STATE_DISABLED ,
                                       API2::TABLE_STATE_SHOW ,
                                       API2::DB_FEILD_SHOW,
                                       API2::UPDATE_STATE_ENABLE);
    _symbolName      = new API2::PARAM("symbolName",
                                       "SYMBOL",
                                       NULL,
                                       API2::UI_ELEMENT_NO_UI ,
                                       API2::DATA_TYPE_STRING ,
                                       API2::UI_STATE_DISABLED ,
                                       API2::TABLE_STATE_SHOW ,
                                       API2::DB_FEILD_HIDE);
    _orderMode       = new API2::PARAM("OrderMode",
                                       "ORDER_MODE",
                                       ui->comboMode,
                                       API2::UI_ELEMENT_COMBO_BOX,
                                       API2::DATA_TYPE_INTEGER,
                                       API2::UI_STATE_ENABLED,
                                       API2::TABLE_STATE_SHOW,
                                       API2::DB_FEILD_SHOW,
                                       API2::UPDATE_STATE_DISABLE) ;
    _totalQuantity   = new API2::PARAM("TotalQuantity",
                                       "QUANTITY",
                                       ui->spinQuantity,
                                       API2::UI_ELEMENT_SPIN_BOX,
                                       API2::DATA_TYPE_SIGNED_LONG,
                                       API2::UI_STATE_ENABLED,
                                       API2::TABLE_STATE_SHOW,
                                       API2::DB_FEILD_SHOW,
                                       API2::UPDATE_STATE_ENABLE);
    _disclosedQuantity = new API2::PARAM("DisclosedQuantity",
                                         "DISCLOSED_QUANTITY",
                                         ui->spinDisclosedQuantity,
                                         API2::UI_ELEMENT_SPIN_BOX,
                                         API2::DATA_TYPE_SIGNED_LONG,
                                         API2::UI_STATE_ENABLED,
                                         API2::TABLE_STATE_SHOW,
                                         API2::DB_FEILD_SHOW,
                                         API2::UPDATE_STATE_ENABLE);
    _limitPrice      = new API2::PARAM("price",
                                       "LIMIT_PRICE",
                                       ui->doubleSpinLimitPrice,
                                       API2::UI_ELEMENT_DOUBLE_SPIN_BOX,
                                       API2::DATA_TYPE_DOUBLE,
                                       API2::UI_STATE_ENABLED ,
                                       API2::TABLE_STATE_SHOW ,
                                       API2::DB_FEILD_SHOW ,
                                       API2::UPDATE_STATE_ENABLE);
    _disclosedQtyPercent = new API2::PARAM("disclosedQtyPercent",
                                           "DISCLOSED_QTY_PERCENT",
                                           ui->doubleSpinDisclosedPercent,
                                           API2::UI_ELEMENT_DOUBLE_SPIN_BOX,
                                           API2::DATA_TYPE_DOUBLE,
                                           API2::UI_STATE_ENABLED ,
                                           API2::TABLE_STATE_SHOW ,
                                           API2::DB_FEILD_SHOW ,
                                           API2::UPDATE_STATE_ENABLE);
    _orderType       = new API2::PARAM("orderType",
                                       "ORDER_TYPE",
                                       ui->comboOrderType,
                                       API2::UI_ELEMENT_COMBO_BOX,
                                       API2::DATA_TYPE_INTEGER,
                                       API2::UI_STATE_ENABLED,
                                       API2::TABLE_STATE_SHOW,
                                       API2::DB_FEILD_SHOW,
                                       API2::UPDATE_STATE_ENABLE);
    _fillType        = new API2::PARAM("fillType",
                                       "FILL_TYPE",
                                       ui->comboFillType,
                                       API2::UI_ELEMENT_COMBO_BOX,
                                       API2::DATA_TYPE_INTEGER,
                                       API2::UI_STATE_ENABLED,
                                       API2::TABLE_STATE_SHOW,
                                       API2::DB_FEILD_SHOW,
                                       API2::UPDATE_STATE_ENABLE);
    _tradedQtyLegOne = new API2::PARAM("tradedQtyLegOne",
                                       "TRQ1",
                                       NULL,
                                       API2::UI_ELEMENT_NO_UI,
                                       API2::DATA_TYPE_UNSIGNED_LONG ,
                                       API2::UI_STATE_DISABLED ,
                                       API2::TABLE_STATE_SHOW ,
                                       API2::DB_FEILD_SHOW);
    _remQty          = new API2::PARAM("remQtyLegOne",
                                       "RQ1",
                                       NULL,
                                       API2::UI_ELEMENT_NO_UI,
                                       API2::DATA_TYPE_UNSIGNED_LONG,
                                       API2::UI_STATE_DISABLED,
                                       API2::TABLE_STATE_SHOW ,
                                       API2::DB_FEILD_HIDE);
    _SIDTotalQty     = new API2::PARAM("SIDTotalQty",
                                       "SID_QTY",
                                       NULL,
                                       API2::UI_ELEMENT_NO_UI,
                                       API2::DATA_TYPE_UNSIGNED_LONG,
                                       API2::UI_STATE_DISABLED ,
                                       API2::TABLE_STATE_SHOW ,
                                       API2::DB_FEILD_HIDE);
     makeParamList();
}

void icebergparams::addParams(API2::PARAM *param,
                              int columnIndex,
                              short filterWidget,
                              bool isEditable,
                              short sortingType )
{
    _paramsMap.insert(param->getParamName(),param);
    param->setColumnIndex(columnIndex);
    param->setFilterType(filterWidget);
    param->setColumnEditable(isEditable);
    param->setSortingType(sortingType);
}

void icebergparams::makeParamList()
{
    short index=1;
    addParams(_strategyVersion);
    addParams(_transactionType);
    addParams(_riskStatus);
    addParams(_sequenceNumber);
    addParams(_clientId);
    addParams(_oldStrategyId);
    addParams(_adminTokenId,
              index++);
    addParams(_strategyId,
              index++,
              API2::WidgetType_LINEEDIT);
    addParams(_state,
              index++,
              API2::WidgetType_COMBOBOX);
    addParams(_portfolioId,
              index++);
    addParams(_strategyComment,
              index++);
    addParams(_orderMode,
              index++,
              API2::WidgetType_MAX,
              false,
              API2::SortingType_String);
    addParams(_symbolIdOne,
              index++);
    addParams(_symbolName,
              index++);
    addParams(_totalQuantity,
              index++,
              API2::WidgetType_MAX,
              true);
    addParams(_limitPrice,
              index++,
              API2::WidgetType_MAX,
              true);
    addParams(_disclosedQuantity,
              index++,
              API2::WidgetType_MAX,
              true);
    addParams(_disclosedQtyPercent,
              index++,
              API2::WidgetType_MAX,
              true);
    addParams(_orderType,
              index++,
              API2::WidgetType_COMBOBOX);
    addParams(_fillType,
              index++,
              API2::WidgetType_COMBOBOX);
    addParams(_tradedQtyLegOne,
              index++);
    addParams(_SIDTotalQty,
              index++);
    addParams(_remQty,
              index++);

    _adminTokenId->setColumnHidden(true);
    _symbolIdOne->setColumnHidden(true);
}
