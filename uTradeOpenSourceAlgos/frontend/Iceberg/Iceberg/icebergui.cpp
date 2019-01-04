#include "icebergui.h"
#include "ui_icebergui.h"
#include "../../FrontEnd_Api_Includes/dll_includes/StrategyConstants.h"

#define FILL_PARAM_UI(param) param->setValue(param->getParamUIValue())
#define SYMBOL_ID "SYMBOL LEG1"
#define ORDER_MODE "Order Mode 1"
#define ACC_DETAIL "Acc Detail 1"
#define LIMIT_PRICE "Limit Price"
#define BUY "Buy"
#define SELL "Sell"
#define ORDER_TYPE "Order Type"
#define FILL_TYPE "Fill Type"
#define QUANTITY "Quantity"
#define TRADED_QUANTITY "Traded Quantity"
#define REMAINING_QUANTITY "Remaining Quantity"
#define DISCLOSED_QUANTITY "Disclosed Qty"
#define DISCLOSED_QUANTITY_PERCENT "Disclosed Qty Percent"
const int timecounter=8;

Icebergui* Icebergui::_Icebergui = 0;
Icebergui::Icebergui(QWidget *parent) :
    ui(new Ui::Icebergui),
    _isNewStrategyWriteMethod(false),
    _time(0),
    _timer(0)
{
    ui->setupUi(this);
    setMinimumSize(sizeHint().width(),
                   sizeHint().height() +
                   50);
}

Icebergui::~Icebergui()
{
    delete ui;
}


void Icebergui::initDisplay()
{
    initialize();
    setWindowFlags( windowFlags() |
                    Qt::WindowMinimizeButtonHint);
    setWindowTitle( "Iceberg - Ver -" +
                    getCommonMethodsWrapper()->getStrategyVersion());
    initializeTabOrder();
    show();
    raise();
    activateWindow();
}

void Icebergui::initialize()
{
    _isNewStrategyWriteMethod =
            getBaseWrapper()->configFileValue(
                "NEW_STRATEGY_WRITE_METHOD");
    ui->groupBoxSource->hide();
    populateElements();
    setConnections();
    _timer.start(800);
}

void Icebergui::setConnections()
{
    connect(ui->comboOrderType,
            SIGNAL(currentTextChanged(QString)),
            this,
            SLOT(onOrderTypeChanged()));
    connect(ui->lineEditLotSize,
            SIGNAL(textChanged(QString)),
            this,
            SLOT(on_editLotSize_textChanged(const QString)));
    connect(ui->pushButtonClose,
            SIGNAL(clicked()),
            this,
            SLOT(onClosePushButtonClicked()));
    connect(&_timer,
            SIGNAL(timeout()),
            this,
            SLOT(updateDataOnTimer()));
}

void Icebergui::on_editLotSize_textChanged(const QString &arg1)
{
    if ( arg1.isEmpty() || arg1 == "0" )
    {
        return;
    }
    int val = arg1.toInt();
    if ( 0 != ui->spinQuantity->value() % val )
    {
        ui->spinQuantity->setValue(val);
    }
    ui->spinQuantity->setSingleStep(val);
    QLineEdit *senderWidget = (QLineEdit *)sender();
    if ( senderWidget == ui->lineEditLotSize )
    {
        setPrecisionDecimal(getBaseWrapper()->
                            getLegsSymbolId(API2::FIRST_LEG));
    }
}

void Icebergui::setPrecisionDecimal(qlonglong symbolId)
{
    const  API2::SymbolDetail &sd =
            getBaseWrapper()->getSymbolIdDetail(symbolId);
    if ( !sd.flag )
    {
        return;
    }
    double stepSize = (double)sd.tickSize/sd.multiplier;
    int lotsize = sd.lotSize;
    ui->spinQuantity->setSingleStep(lotsize);
    ui->doubleSpinLimitPrice->setDecimals(sd.precision);
    ui->doubleSpinLimitPrice->setSingleStep(stepSize);
    ui->spinDisclosedQuantity->setSingleStep(lotsize);
}

bool Icebergui::isSpreadAlgo()
{
    return false;
}

void  Icebergui::populateElements()
{
    setSymbolPanel();
    _iceBergParams = new icebergparams(ui);
    _paramsMap = &_iceBergParams->getParamList();
    ui->buttonPanel->addWidget(getBaseWrapper()->getButtonPanel());
    getBaseWrapper()->hideButtons(API2::CTRL_BTN_MINIMIZE);
    getBaseWrapper()->hideButtons(API2::CTRL_BTN_SETTINGS);
    getBaseWrapper()->addtoParamsGroup(_paramsMap);
    getBaseWrapper()->addToMainStrategyWindow(ui->tableview);
    getBaseWrapper()->setStrategyContainer(
                ui->groupBox,
                ui->pushButtonClose);
    _baseTableModel = getBaseWrapper()->getTableModel();
    getBaseWrapper()->setStrategyInSingleRow(0);
    setFilters();
    populateOrderTypes();
    populateFillTypes();
    setDefaultIndex();
}

void Icebergui :: onOrderTypeChanged()
{
    if ( ui->comboOrderType->currentText() == "Market" )
    {
        ui->doubleSpinLimitPrice->setEnabled(false);
    }
    else
    {
        ui->doubleSpinLimitPrice->setEnabled(true);
    }
}

void Icebergui::setFilters()
{
    QComboBox *filterComboBox;
    filterComboBox =  getBaseWrapper()->
            getFilterWidgetComboBox(
                _iceBergParams->_state->getColumnIndex());
    filterComboBox->addItem(STRATEGY_CONST::ALL);
    filterComboBox->addItem(STRATEGY_CONST::READY_STATE);
    filterComboBox->addItem(STRATEGY_CONST::RUN_STATE);
    filterComboBox->addItem(STRATEGY_CONST::AWAITED);
    filterComboBox->setCurrentIndex(0);

    filterComboBox = getBaseWrapper()->getFilterWidgetComboBox(_iceBergParams->_orderType->getColumnIndex());
    filterComboBox->addItem(STRATEGY_CONST::ALL);
    getBaseWrapper()->populateOrderType(filterComboBox);
    filterComboBox->setCurrentIndex(0);

    filterComboBox = getBaseWrapper()->getFilterWidgetComboBox(_iceBergParams->_fillType->getColumnIndex());
    filterComboBox->addItem(STRATEGY_CONST::ALL);
    populateFillType(filterComboBox);
    filterComboBox->setCurrentIndex(0);
}

void Icebergui::populateFillType(QComboBox * combofill)
{
    combofill->addItem(getCommonMethodsWrapper()->
                       getOrderValidityStr(fill_Type_DAY));
    combofill->addItem(getCommonMethodsWrapper()->
                       getOrderValidityStr(fill_Type_IOC));
}

void Icebergui::setSymbolPanel()
{
    SymbolPanelElements *symbolPanelElementsCashPrimary =
            new SymbolPanelElements(ui->comboMode,
                                    ui->comboSource,
                                    ui->comboMarket,
                                    ui->comboInstrument,
                                    ui->verticalLayout_4,
                                    ui->comboSeries,
                                    ui->comboExpiry,
                                    ui->comboOptMode,
                                    ui->comboStrike,
                                    ui->lineEditLotSize,
                                    ui->radioClient,
                                    ui->radioPro,
                                    ui->lineEditPartCode,
                                    ui->comboAccount );
    short instrument = 0;
    instrument = API2::STOCK |
            API2::FUTURE |
            API2::OPTION;
    getBaseWrapper()->addSymbolPanel(instrument,
                                     symbolPanelElementsCashPrimary,
                                     false,
                                     true);
    ui->comboMarket->setCurrentIndex(
                ui->comboMarket->findText(
                    getCommonMethodsWrapper()->
                    getMarket(API2::CONSTANTS::CMD_ExchangeId_ESM)));
    ui->comboInstrument->setCurrentIndex(
                ui->comboInstrument->findText("STOCK"));
    ui->comboSeries->setCurrentIndex(ui->comboSeries->findText("EQ"));
    ui->radioClient->setEnabled(true);
    ui->comboAccount->setEnabled(false);
    ui->lineEditPartCode->setEnabled(false);
    ui->lineEditLotSize->setEnabled(false);
    getBaseWrapper()->initializeFirstLegSignals();
}

void Icebergui::populateOrderTypes()
{
    ui->comboOrderType->addItem("Limit");
    ui->comboOrderType->addItem("Market");
}

void Icebergui::populateFillTypes()
{
    ui->comboFillType->addItem("DAY");
    ui->comboFillType->addItem("IOC");
}

void Icebergui::setDefaultIndex()
{
    getBaseWrapper()->_col.adminTokenIdIndex =
            _iceBergParams->_adminTokenId->getColumnIndex();
    getBaseWrapper()->_col.stateIndex =
            _iceBergParams->_state->getColumnIndex();
    getBaseWrapper()->_col.strategyIdIndex =
            _iceBergParams->_strategyId->getColumnIndex();
    getBaseWrapper()->_col.strategyCommentIndex =
            _iceBergParams->_strategyComment->getColumnIndex();
    getBaseWrapper()->_col.portFolioIdIndex =
            _iceBergParams->_portfolioId->getColumnIndex();
    getBaseWrapper()->_col.orderMode =
            _iceBergParams->_orderMode->getColumnIndex();
    getBaseWrapper()->_col.symbolIdLeg1 =
            _iceBergParams->_symbolIdOne->getColumnIndex();
    getBaseWrapper()->_col.sidQtyLeg1Index =
            _iceBergParams->_SIDTotalQty->getColumnIndex();
}

void Icebergui::onAddPushButtonClicked()
{
    getBaseWrapper()->on_AddPushButton_Clicked();
}

void Icebergui::updateSymbolIdsDetail(int row, bool isUpdateAll)
{
    if ( row == -1 )
    {
        return;
    }
    int start=row;
    int end =row+1;
    if ( isUpdateAll )
    {
        start = 0;
        end = _baseTableModel->rowCount();
        getBaseWrapper()->_hashRowSymboID.clear();
    }
    for ( int counter = start; counter<end; ++counter )
    {
        getBaseWrapper()->insertHashRowSymbolId(
                    row,
                    _iceBergParams->_symbolIdOne->getColumnIndex(),
                    _baseTableModel->item(
                        counter,
                        _iceBergParams->_totalQuantity->
                        getColumnIndex())->data(
                        Qt::DisplayRole).toLongLong(),
                    _iceBergParams->_orderMode->getColumnIndex(),
                    STRATEGY_TYPE_MAX);
    }
}

bool Icebergui::buildCommandFromUi(API2::PORTFOLIO_STATE state)
{
    _iceBergParams->_adminTokenId->setValue(0);
    _iceBergParams->_clientId->setValue(getBaseWrapper()->getUserId());
    _iceBergParams->_strategyId->setValue(0);
    _iceBergParams->_riskStatus->setValue(API2::CONSTANTS::RSP_RiskStatus_MAX);
    _iceBergParams->_portfolioId->setValue(getBaseWrapper()->getPortFolioId());
    _iceBergParams->_state->setValue(API2::CONSTANTS::RSP_ResponseType_MAX);
    _iceBergParams->_strategyComment->setValue(API2::CONSTANTS::RSP_StrategyComment_MAX);
    _iceBergParams->_transactionType->setValue(API2::CONSTANTS::CMD_TransactionType_NEW);
    qlonglong symbolIdOne = getBaseWrapper()->getLegsSymbolId(API2::FIRST_LEG);
    const  API2::SymbolDetail &symbolDetailOne = getBaseWrapper()->getSymbolIdDetail(symbolIdOne);
    _iceBergParams->_symbolIdOne->setValue(symbolIdOne);
    _iceBergParams->_symbolName->setValue(symbolDetailOne.scripName);
    foreach ( QString key,_paramsMap->keys() )
    {
        if ( _paramsMap->value(key)->isGui() )
        {
            FILL_PARAM_UI(_paramsMap->value(key));
        }
    }
    _iceBergParams->_orderType->setValue(getOrderType( ui->comboOrderType->currentText()));
    _iceBergParams->_fillType->setValue(getCommonMethodsWrapper()->getOrderValidity( ui->comboFillType->currentText()));
    _iceBergParams->_totalQuantity->setValue(ui->spinQuantity->value());
    _iceBergParams->_disclosedQuantity->setValue(ui->spinDisclosedQuantity->value());
    return true;
}

int Icebergui::getPortfolioId(int strategyId)
{
    QSqlQuery query;
    int portfolioId = 0;
    QHash<int,int>::iterator it =
            _hashStrategyIdPortfolioId.find(strategyId);
    if ( it != _hashStrategyIdPortfolioId.end() )
    {
        portfolioId = _hashStrategyIdPortfolioId.value(strategyId);
    }
    if ( !portfolioId )
    {
        query.prepare("SELECT " + _iceBergParams->_portfolioId->getParamName() + " FROM "+getBaseWrapper()->getstrategyName()+ " WHERE " + _iceBergParams->_strategyId->getParamName() + " = :" + _iceBergParams->_strategyId->getParamName());
        query.bindValue(":" + _iceBergParams->_strategyId->getParamName(), strategyId);

        if ( !query.exec() )
        {
            getBaseWrapper()->printSqlError(query,__FILE__,Q_FUNC_INFO,__LINE__);
        }

        if ( query.next() )
        {

            portfolioId = query.value(0).toLongLong();
            if ( portfolioId > 0 )
            {
                _hashStrategyIdPortfolioId.insert(
                            strategyId,
                            portfolioId);
            }
        }
    }
    return portfolioId;
}

bool Icebergui::showSpreadPopup()
{
    return true;
}

bool Icebergui::isSpreadCalculationAllowed()
{
    return false;
}

bool Icebergui::isPortfolioNamePresent()
{
    return false;
}

bool Icebergui::isSidTotalQtyHandling()
{
    return false;
}

void Icebergui::setApiCommand(API2::UserParams *apiParams,
                              QSqlRecord &record,
                              int stgCount,
                              short type)
{
    getBaseWrapper()->setCommandCategory(API2::CONSTANTS::CMD_CommandCategory_API2_STRATEGY);
    qlonglong adminTokenId = record.value(_iceBergParams->_adminTokenId->getParamName()).toLongLong();
    apiParams->setAdminTokenId(adminTokenId);
    apiParams->setClientId(getBaseWrapper()->getUserId());
    apiParams->setSequenceNumber(0);
    apiParams->setStrategyId(record.value(_iceBergParams->_strategyId->getParamName()).toLongLong());
    apiParams->setTransactionType(type);
    apiParams->setStrategyVersion(0);
    apiParams->setValue(SYMBOL_ID,record.value(_iceBergParams->_symbolIdOne->getParamName()).toLongLong());
    apiParams->setValue(ORDER_MODE,TO_QT_COMPATIBLE_ASCII( record.value(_iceBergParams->_orderMode->getParamName()).toChar() ) );
    apiParams->setValue(ACC_DETAIL,getBaseWrapper()->getAccountDetailFromDb(adminTokenId,API2::FIRST_LEG));
    apiParams->setValue(ORDER_TYPE,TO_QT_COMPATIBLE_ASCII( record.value(_iceBergParams->_orderType->getParamName()).toChar() ) );
    apiParams->setValue(LIMIT_PRICE,record.value(_iceBergParams->_limitPrice->getParamName()).toLongLong());
    apiParams->setValue(DISCLOSED_QUANTITY,record.value(_iceBergParams->_disclosedQuantity->getParamName()).toLongLong());
    apiParams->setValue(FILL_TYPE,TO_QT_COMPATIBLE_ASCII( record.value(_iceBergParams->_fillType->getParamName()).toChar() ) );
    apiParams->setValue(DISCLOSED_QUANTITY_PERCENT,record.value(_iceBergParams->_disclosedQtyPercent->getParamName()).toLongLong());
    apiParams->setValue(QUANTITY,record.value(_iceBergParams->_totalQuantity->getParamName()).toLongLong()/ui->lineEditLotSize->text().toInt());
#ifdef DEBUG
    apiParams->dump();
#endif
}

qlonglong Icebergui::getCurrentStrategyId()
{
    QModelIndex index = getBaseWrapper()->getCurrentIndex();
    if ( index.isValid() )
    {
        int row =index.row();
        if ( row != -1 &&
             getBaseWrapper()->getStrategyState(row) ==
             STRATEGY_CONST::RUN_STATE )
        {
            return getBaseWrapper()->getTableData(
                        index.row(),
                        _iceBergParams->_strategyId->
                        getColumnIndex()).toLongLong();
        }
    }
    return 0;
}

bool Icebergui::validatePortFolioDataOnLoadOld(qlonglong adminTokenId)
{
    QSqlQuery query= getBaseWrapper()->fillDetailsFromAdminTokenId(adminTokenId,STRATEGY_CONST::ADMIN_TOKEN_ID);
    if ( query.next() )
    {
        QSqlRecord record = query.record();
        if ( !isOrdertypeValid(
                 record.value(_iceBergParams->
                              _orderType->getParamName()).toInt()) )
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool Icebergui::validatePortFolioData(QStringList &dataList,
                                      QString &errorText,
                                      int portfolioCount)
{
    int orderTypeDbIndex = getBaseWrapper()->getDbIndex(_iceBergParams->_orderType->getParamName());
    if ( orderTypeDbIndex != -1 )
    {
        if ( !isOrdertypeValid(dataList.at(orderTypeDbIndex).toInt()) )
        {
            errorText =QString("Portfolio %1 :").arg(QString::number(portfolioCount));
            errorText.push_back("Order Type Not Allowed");
            return false;
        }
    }
    return true;
}

bool Icebergui::isOrdertypeValid(const int &orderType)
{
    return true;
}

bool Icebergui::validateData(API2::PORTFOLIO_STATE state)
{
    if ( !getBaseWrapper()->validateData(API2::FIRST_LEG) )
    {
        displayWarningMessage("Symbol Data Invalid for Primary Cash Leg ");
        return false;
    }
    if ( ui->comboOrderType->currentText().isEmpty() )
    {
        QMessageBox::warning(this,getBaseWrapper()->getFileName(),trUtf8("Invalid Order Type"));
        ui->comboOrderType->setFocus();
        getBaseWrapper()->resetWidgetStateOnValidation(state,_iceBergParams->_orderType);
        return false;
    }
    qlonglong symbolId = getBaseWrapper()->getLegsSymbolId(API2::FIRST_LEG);
    const API2:: SymbolDetail &sd = getBaseWrapper()->getSymbolIdDetail(symbolId);
    qlonglong disclqnty = QString::number(ui->spinDisclosedQuantity->value(),'f',sd.precision).remove(".").toLongLong();
    qlonglong totalQty = QString::number(ui->spinQuantity->value(),'f',sd.precision).remove(".").toLongLong();
    qlonglong discqtypcnt = QString::number(ui->doubleSpinDisclosedPercent->value(),'f',sd.precision).remove(".").toLongLong();
    QString priceVal = QString::number(ui->doubleSpinLimitPrice->value(),'f',sd.precision);
    priceVal.remove(QLocale::system().decimalPoint());
    if ( !totalQty )
    {
        QMessageBox::warning(this,
                             getBaseWrapper()->getFileName(),
                             trUtf8("Quantity must be greater than 0"));
        ui->spinQuantity->setFocus();
        getBaseWrapper()->resetWidgetStateOnValidation(state,_iceBergParams->_totalQuantity);
        return false;
    }
    if ( totalQty % ui->lineEditLotSize->text().toInt()!=0 )
    {
        QMessageBox::warning(this,
                             getBaseWrapper()->getFileName(),
                             trUtf8("Quantity Should be Multiple of LotSize"));
        ui->spinQuantity->setFocus();
        getBaseWrapper()->resetWidgetStateOnValidation(state,_iceBergParams->_totalQuantity);
        return false;
    }
    if ( !priceVal.toLongLong() && ui->comboOrderType->currentIndex() == 0 )
    {
        QMessageBox::warning(this,
                             getBaseWrapper()->getFileName(),
                             trUtf8("Limit Price must be greater than 0"));
        ui->doubleSpinLimitPrice->setFocus();
        return false;
    }
    if ( totalQty < disclqnty )
    {
        QMessageBox::warning(this,
                             getBaseWrapper()->getFileName(),
                             trUtf8("Disclosed Quantity must be less than or"
                                    " equal to Quantity"));
        ui->spinDisclosedQuantity->setFocus();
        return false;
    }
    if ( !disclqnty && !discqtypcnt )
    {
        QMessageBox::warning(this,
                             getBaseWrapper()->getFileName(),
                             tr("Both Disclosed Quantity and Disclosed Quantity "
                                "Percent can't be Zero. Fill Atleast One"));
        return false;
    }
    return true;
}

void Icebergui :: displayWarningMessage(const QString &Message)
{
    QMessageBox::warning(this,
                         getBaseWrapper()->getFileName(),
                         trUtf8(Message.toStdString().c_str()));
}

void Icebergui :: updateRemainingFeilds(int row,
                                        QSqlRecord &adminTokenIdData)
{
    short precision = 0;
    double multiplier  = 0.00;
    QList<qlonglong> symbolIdList;
    symbolIdList << adminTokenIdData.value(_iceBergParams->_symbolIdOne->getParamName()).toLongLong();
    _baseTableModel->blockSignals(true);
    getBaseWrapper()->getPrecisionAndMultiplier(adminTokenIdData.value(_iceBergParams->_symbolIdOne->getParamName()).toLongLong(),multiplier,precision);
    getBaseWrapper()->setTableData(row,_iceBergParams->_symbolIdOne->getColumnIndex(),adminTokenIdData.value(_iceBergParams->_symbolIdOne->getParamName()).toLongLong());
    getBaseWrapper()->setTableData(row,_iceBergParams->_symbolName->getColumnIndex(),getBaseWrapper()->getScripName(adminTokenIdData.value(_iceBergParams->_symbolIdOne->getParamName()).toLongLong()));
    getBaseWrapper()->setTableData(row,_iceBergParams->_state->getColumnIndex(),getCommonMethodsWrapper()->getStrategyState(adminTokenIdData.value(_iceBergParams->_state->getParamName()).toInt()));
    QStringList accountDetailList;
    getBaseWrapper()->getAccountDetailList(getBaseWrapper()->getTableData(row,_iceBergParams->_adminTokenId->getColumnIndex()).toLongLong(),symbolIdList,accountDetailList);
    updateTradedQty(row);
    updateRemainingQty(row);
    _baseTableModel->blockSignals(false);
}

void Icebergui::onRunPushButtonClicked()
{
    QModelIndex index = getBaseWrapper()->getCurrentIndex();
    if ( index.isValid() )
    {
        getBaseWrapper()->runStrategy(index.row());
    }
    getBaseWrapper()->updateTableView();
}

void Icebergui::onAltMPressed()
{
    QModelIndex index = getBaseWrapper()->getCurrentIndex();
    if ( !index.isValid() )
    {
        return;
    }
    int row = index.row();
    QSqlRecord recordsOld;
    const API2::SymbolDetail &sd = getBaseWrapper()->getSymbolIdDetail(getBaseWrapper()->getTableData(row, _iceBergParams->_symbolIdOne->getColumnIndex()).toLongLong());
    getBaseWrapper()->getEditableFieldData(getBaseWrapper()->getTableData(row,_iceBergParams->_adminTokenId->getColumnIndex()).toLongLong(),recordsOld);
    qlonglong oldQty =recordsOld.value(_iceBergParams->_totalQuantity->getParamName()).toLongLong();
    double oldPrice = recordsOld.value(_iceBergParams->_limitPrice->getParamName()).toDouble();
    if ( getBaseWrapper()->getEditableModeRow() == -1 &&
         !getBaseWrapper()->isTableViewFocused() )
    {
        return;
    }
    getBaseWrapper()->setEditableModeRow(-1);
    getBaseWrapper()->setFocus();
    getBaseWrapper()->getEditableFieldData(getBaseWrapper()->getTableData(row,_iceBergParams->_adminTokenId->getColumnIndex()).toLongLong(),recordsOld);
    setFocus();
    if ( row != -1 )
    {
        qlonglong totalQty = getBaseWrapper()->getTableData(row, _iceBergParams->_totalQuantity->getColumnIndex()).toLongLong();
        double price = getBaseWrapper()->getTableData(row,_iceBergParams->_limitPrice->getColumnIndex()).toDouble();
        if ( oldPrice != price || totalQty != oldQty )
        {
            ui->spinQuantity->setValue(getBaseWrapper()->getTableData(row,_iceBergParams->_totalQuantity->getColumnIndex()).toLongLong());
            ui->doubleSpinLimitPrice->setValue(getBaseWrapper()->getTableData(row,_iceBergParams->_limitPrice->getColumnIndex()).toDouble());
            if ( getBaseWrapper()->getTableData(
                     row,_iceBergParams->_state->getColumnIndex()) ==
                 STRATEGY_CONST::RUN_STATE )
            {
                getBaseWrapper()->runStrategy(row);
            }
            else
            {
                getBaseWrapper()->on_CommitPushButton_Clicked();
            }
        }
    }
}

void Icebergui::receiveStrategyResponse(API2::Strategy &strategyResponse)
{
    QSharedPointer<API2::Strategy>  strategyResponseSharedPtr  = QSharedPointer<API2::Strategy>(new API2::Strategy(strategyResponse));
    getBaseWrapper()->receiveStrategyResponse(strategyResponseSharedPtr);
}

void Icebergui::onNewPushButtonClicked()
{
    getBaseWrapper()->on_NewPushButton_Clicked();
    setExpiryDate();
    ui->spinQuantity->setValue(ui->lineEditLotSize->text().toInt());
    ui->spinDisclosedQuantity->setValue(ui->lineEditLotSize->text().toInt());
    ui->comboMode->setFocus();
    ui->comboOrderType->setEnabled(true);
}

void Icebergui::onEditPushButtonClicked()
{
    QModelIndex index = getBaseWrapper()->getCurrentIndex();
    if ( !index.isValid() )
    {
        return;
    }
    int row = index.row();
    ui->comboOrderType->setDisabled(true);
    getBaseWrapper()->on_EditPushButton_Clicked(row);
}

void Icebergui::onCommitPushButtonClicked()
{
    getBaseWrapper()->on_CommitPushButton_Clicked();
}

void Icebergui::onRemoveAllClicked()
{
    getBaseWrapper()->on_RemoveAll_Clicked();
}

void Icebergui::onRemovePushButtonClicked()
{
    getBaseWrapper()->on_RemovePushButton_Clicked();
}

void Icebergui::onStopAllPushButtonclicked()
{
    getBaseWrapper()->on_StopAllPushButton_clicked();
}

void Icebergui::onStopPushButtonClicked()
{
    getBaseWrapper()->on_StopPushButton_Clicked();
}

void Icebergui::populateUIPanels(int row,
                                 QSqlRecord &record,
                                 bool isNew)
{
    if ( row ==-1 )
    {
        return;
    }
    ui->spinQuantity->setValue(record.value(_iceBergParams->_totalQuantity->getParamName()).toLongLong());
    ui->doubleSpinLimitPrice->setValue(record.value(_iceBergParams->_limitPrice->getParamName()).toDouble()/100);
    ui->doubleSpinDisclosedPercent->setValue(record.value(_iceBergParams->_disclosedQtyPercent->getParamName()).toDouble()/100);
    ui->spinDisclosedQuantity->setValue(record.value(_iceBergParams->_disclosedQuantity->getParamName()).toLongLong());
    ui->comboOrderType->setCurrentIndex(ui->comboOrderType->findText(getCommonMethodsWrapper()->getOrderTypeStr(record.value(_iceBergParams->_orderType->getParamName()).toInt())));
    getBaseWrapper()->enableAccountDetailUI(API2::FIRST_LEG,isNew);
    if ( !isNew )
    {
        getBaseWrapper()->populateLeg(API2::FIRST_LEG,record.value(_iceBergParams->_symbolIdOne->getParamName()).toLongLong(),record.value(_iceBergParams->_adminTokenId->getParamName()).toLongLong());
    }
}

short Icebergui::getOrderType(const QString &orderType)
{
    if ( orderType ==
         getCommonMethodsWrapper()->getOrderTypeStr(order_Type_LIMIT) )
    {
        return order_Type_LIMIT;
    }
    else if ( orderType ==
              getCommonMethodsWrapper()->getOrderTypeStr(order_Type_MARKET) )
    {
        return order_Type_MARKET;
    }
    return order_Type_MAX;
}

void Icebergui::updateDataOnTimer()
{
    int updateCounter = 0;
    if ( !_isNewStrategyWriteMethod )
    {
        while ( !getBaseWrapper()->_responseQueue.isEmpty() )
        {
            getBaseWrapper()->updateResponse(getBaseWrapper()->_responseQueue.dequeue());
            if ( updateCounter++==timecounter )
            {
                break;
            }
        }
    }
    if ( !getBaseWrapper()->isProcessingEvent() )
    {
        getBaseWrapper()->updateTableView();
    }
}

void Icebergui::updateTradesinDb(qlonglong adminTokenId,
                                 int filledQuantity)
{
    QSqlQuery query;
    query.prepare("UPDATE "+ getBaseWrapper()->getstrategyName() + " SET " + _iceBergParams->_tradedQtyLegOne->getParamName() + "=:" + _iceBergParams->_tradedQtyLegOne->getParamName() + " WHERE " + _iceBergParams->_adminTokenId->getParamName() + "=:" + _iceBergParams->_adminTokenId->getParamName());
    query.bindValue(":" + _iceBergParams->_tradedQtyLegOne->getParamName(),getTradedQuantity(adminTokenId)+filledQuantity);
    query.bindValue(":" + _iceBergParams->_adminTokenId->getParamName(), adminTokenId);
    if ( !query.exec() )
    {
        getBaseWrapper()->printSqlError(query);
    }
}

long long Icebergui::getTradedQuantity(qlonglong adminTokenId)
{
    long long  result = 0;
    QSqlQuery query;
    query.prepare("select " + _iceBergParams->_tradedQtyLegOne->getParamName() + " from "+getBaseWrapper()->getstrategyName()+" where " + _iceBergParams->_adminTokenId->getParamName() +" = :" + _iceBergParams->_adminTokenId->getParamName());
    query.bindValue(":" + _iceBergParams->_adminTokenId->getParamName(),adminTokenId);
    if ( query.exec() && query.next() )
    {
        result = query.value(0).toInt();
    }
    else
    {
        getBaseWrapper()->printSqlError(query);
    }
    return result;
}

void Icebergui::updateTrades(const RSP::OrderConfirmation &orderConfirmation)
{
    qlonglong totalQty = 0;
    qlonglong tradedQty = 0;
    QSqlQuery query;
    query.prepare("SELECT " + _iceBergParams->_symbolIdOne->getParamName() + ", " + _iceBergParams->_adminTokenId->getParamName() + ", " + _iceBergParams->_portfolioId->getParamName() + " FROM " +getBaseWrapper()->getstrategyName() + " WHERE " + _iceBergParams->_strategyId->getParamName() + " =:" + _iceBergParams->_strategyId->getParamName() + " order by "+_iceBergParams->_adminTokenId->getParamName() + " desc");
    query.bindValue(":"+_iceBergParams->_strategyId->getParamName(),orderConfirmation.getStrategyId());
    if ( !query.exec() )
    {
        getBaseWrapper()->printSqlError(query, __FILE__, Q_FUNC_INFO, __LINE__);
        return;
    }
    if ( query.next() )
    {
        QSqlRecord rec = query.record();
        qlonglong adminTokenId = query.value(rec.indexOf(_iceBergParams->_adminTokenId->getParamName())).toLongLong();
        qlonglong portfolioId = query.value(rec.indexOf(_iceBergParams->_portfolioId->getParamName())).toLongLong();
        int row = -1;
        row = getBaseWrapper()->getStrategyRowFromAdminTokenId(adminTokenId);
        // handling of TRADE AFTER TERMINATION
        if ( row == -1 )
        {
            QSqlQuery query;
            query.prepare("Select MAX(" + _iceBergParams->_adminTokenId->getParamName() + ") from " + getBaseWrapper()->getstrategyName() + " WHERE " + _iceBergParams->_portfolioId->getParamName()+ " =:" + _iceBergParams->_portfolioId->getParamName());
            query.bindValue(":"+_iceBergParams->_portfolioId->getParamName(),portfolioId);
            if ( !query.exec() )
            {
                getBaseWrapper()->printSqlError(query, __FILE__, Q_FUNC_INFO, __LINE__);
            }
            else if ( query.next() )
            {
                adminTokenId = query.value(0).toLongLong();
                row = getBaseWrapper()->getStrategyRowFromAdminTokenId(adminTokenId);
            }
        }
        if ( row!=-1 )
        {
            QString tradedParamName;
            totalQty= getBaseWrapper()->getTableData(row,_iceBergParams->_totalQuantity->getColumnIndex()).toLongLong();
            _baseTableModel->blockSignals(true);
            if ( orderConfirmation.getSymbolId() ==
                 query.value(rec.indexOf(_iceBergParams->_symbolIdOne->getParamName())).toULongLong() )
            {
                tradedQty = getBaseWrapper()->getTableData(row,_iceBergParams->_tradedQtyLegOne->getColumnIndex()).toLongLong() + orderConfirmation.getLastFillQuantity();
                getBaseWrapper()->setTableData(row,_iceBergParams->_tradedQtyLegOne->getColumnIndex(),tradedQty);
                tradedParamName = _iceBergParams->_tradedQtyLegOne->getParamName();
            }
            // Updating Remaining Quantity in UI
            qlonglong totalTradedQuantity = getBaseWrapper()->getTableData(row,_iceBergParams->_tradedQtyLegOne->getColumnIndex()).toLongLong();
            getBaseWrapper()->setTableData(row,_iceBergParams->_remQty->getColumnIndex(),totalQty-totalTradedQuantity);
            _baseTableModel->blockSignals(false);
            query.prepare("UPDATE " + getBaseWrapper()->getstrategyName() + " SET " + tradedParamName + " = :" + tradedParamName + " WHERE " + _iceBergParams->_strategyId->getParamName() + " =:" + _iceBergParams->_strategyId->getParamName());
            query.bindValue(":"+tradedParamName,tradedQty);
            query.bindValue(":"+_iceBergParams->_strategyId->getParamName(),orderConfirmation.getStrategyId());
            if ( !query.exec() )
            {
                getBaseWrapper()->printSqlError(query, __FILE__, Q_FUNC_INFO, __LINE__);
            }
        }
    }
}

bool Icebergui::setTotalQtyForLegs(int row,
                                   short transactiontype,
                                   QSqlRecord &oldRecord,
                                   const QList<BaseSymbolIds *> &symbolIdsList)
{
    bool isValidQty = true;
    qlonglong tradedQty = getBaseWrapper()->getTableData(row,_iceBergParams->_tradedQtyLegOne->getColumnIndex()).toLongLong();
    qlonglong totalQty =0;
    qlonglong sidqty = getBaseWrapper()->getTableData(row,_iceBergParams->_SIDTotalQty->getColumnIndex()).toLongLong();
    qlonglong pid = getBaseWrapper()->getTableData(row,_iceBergParams->_portfolioId->getColumnIndex()).toLongLong();
    if ( API2::CONSTANTS::CMD_TransactionType_NEW==transactiontype )
    {
        totalQty = oldRecord.value(_iceBergParams->_totalQuantity->getParamName()).toLongLong() - tradedQty;
        if ( !isTotalQtyValidOnNew(row) )
        {
            QMessageBox::warning(this,
                                 getBaseWrapper()->getFileName(),
                                 tr("Total Quantity must be greater"
                                    " then Traded Quantity"));
            return false;
        }
    }
    else if ( API2::CONSTANTS::CMD_TransactionType_MODIFY ==
              transactiontype )
    {
        isValidQty = isValidQty;
        if ( isValidQty )
        {
            _pidSidQty[pid]=sidqty;
            totalQty = sidqty + (ui->spinQuantity->value() - oldRecord.value(_iceBergParams->_totalQuantity->getParamName()).toLongLong());
        }
    }
    isValidQty = isValidQty && (totalQty > 0 ? true :false);
    if ( isValidQty )
    {
        quantity = totalQty;
        _baseTableModel->blockSignals(true);
        getBaseWrapper()->setTableData(row,_iceBergParams->_SIDTotalQty->getColumnIndex(),quantity);
        _baseTableModel->blockSignals(false);
    }
    else
    {
        displayWarningMessage("Total Quantity must be greater then Traded Quantity");
        return false;
    }
    return isValidQty;
}

bool Icebergui::isTotalQtyVailid(int row)
{
    return ( ui->spinQuantity->value() -  ( getBaseWrapper()->getTableData(row,_iceBergParams->_tradedQtyLegOne->getColumnIndex() ).toLongLong()  ) ) > 0  ;
}

bool Icebergui::isTotalQtyValidOnNew(int row)
{
    return (getBaseWrapper()->getTableData(row,_iceBergParams->_totalQuantity->getColumnIndex()).toLongLong() - ( getBaseWrapper()->getTableData(row,_iceBergParams->_tradedQtyLegOne->getColumnIndex() ).toLongLong()  ) ) > 0 ;
}

bool Icebergui::updateRemainingQty(int row)
{
    bool isRemQtyValid = true;
    qlonglong remQty =0;
    remQty = getBaseWrapper()->getTableData(row,_iceBergParams->_totalQuantity->getColumnIndex()).toLongLong() -
            (getBaseWrapper()->getTableData(row,_iceBergParams->_tradedQtyLegOne->getColumnIndex()).toLongLong());
    if ( remQty<=0 )
    {
        isRemQtyValid=false;
    }
    _baseTableModel->blockSignals(true);
    getBaseWrapper()->setTableData(row,_iceBergParams->_remQty->getColumnIndex(),remQty);
    _baseTableModel->blockSignals(false);
    return isRemQtyValid;
}


void Icebergui::getDllVersionString(QString &dllVersionString)
{
    dllVersionString = DLL_VERSION_STRING;
}

void Icebergui::updateEditableFieldColor(int row, QColor color)
{
    getBaseWrapper()->setColumnBackGround(row,_iceBergParams->_disclosedQuantity->getColumnIndex(),color);
    getBaseWrapper()->setColumnBackGround(row,_iceBergParams->_disclosedQtyPercent->getColumnIndex(),color);
    getBaseWrapper()->setColumnBackGround(row,_iceBergParams->_totalQuantity->getColumnIndex(),color);
    getBaseWrapper()->setColumnBackGround(row,_iceBergParams->_limitPrice->getColumnIndex(),color);

}

void Icebergui::setExpiryDate()
{
    getCommonMethodsWrapper()->getNextMonthExpiry(ui->comboExpiry);
}

void Icebergui::applyUIValidation(short transactionType, short state)
{
    bool isNew = transactionType == API2::CONSTANTS::CMD_TransactionType_NEW;
    getBaseWrapper()->enableSymbolPanel(API2::FIRST_LEG,isNew ? true : false,true);
}

void Icebergui::allUIValidation(int row, short strategy)
{
    getBaseWrapper()->enableSymbolPanel(API2::FIRST_LEG,true,true,false);
}


void Icebergui::updateAccountDetail(const int row)
{
    getBaseWrapper()->updateAccountDetailOnEdit(row,_iceBergParams->_adminTokenId->getColumnIndex(),API2::FIRST_LEG);
}

void Icebergui::onCtrlSpacePressed()
{
    getBaseWrapper()->onCtrlSpacePressed();
}

void Icebergui::onEscapePressed()
{
    getBaseWrapper()->onEscapePressed();
}

void Icebergui::onUpKeyPressed()
{
    getBaseWrapper()->onUpKeyPressed();
}

void Icebergui::OnDownKeyPressed()
{
    getBaseWrapper()->OnDownKeyPressed();
}

void Icebergui::onClosePushButtonClicked()
{
    ui->pushButtonClose->setText(ui->groupBox->isVisible() ? "+" : "-");
    ui->groupBox->setVisible(!ui->groupBox->isVisible());
}

void Icebergui::updateTradedQty(int row)
{
    QSqlQuery sqlQuery;
    int pid = getBaseWrapper()->getTableData(row,_iceBergParams->_portfolioId->getColumnIndex()).toInt();
    QString key = "MAX("+_iceBergParams->_tradedQtyLegOne->getParamName()+")";
    sqlQuery.prepare("select " + key + " from "+ getBaseWrapper()->getstrategyName() + " where portfolioId=:portfolioId ");
    sqlQuery.bindValue(":portfolioId",pid);
    if ( !sqlQuery.exec() )
    {
        getBaseWrapper()->printSqlError(sqlQuery);
    }
    if ( sqlQuery.next() )
    {
        getBaseWrapper()->setTableData(row,_iceBergParams->_tradedQtyLegOne->getColumnIndex(),sqlQuery.value(0).toLongLong());
    }
}

bool Icebergui::isStrategyLegPresent()
{
    return false;
}

void Icebergui::updateSidQty(qlonglong row)
{
    qlonglong pid = getBaseWrapper()->getTableData(row,_iceBergParams->_portfolioId->getColumnIndex()).toLongLong();
    QHash<qlonglong,qlonglong >::iterator itr = _pidSidQty.find(pid);
    if ( itr != _pidSidQty.end() )
    {
        getBaseWrapper()->setTableData(row,_iceBergParams->_SIDTotalQty->getColumnIndex(),itr.value());
    }
}

void Icebergui::receiveCustomResponse(API2::API2_CustomResponse &apiCustomResponse)
{
    std::list<std::string> dataList = apiCustomResponse.getUiDataPair();
    QStringList keyValueList;
    QString key;
    long long value;
    long long sIdQtyNew=0;
    long long _tradedQuantity = 0;
    long long _remainingQuantity = 0;
    int row = getBaseWrapper()->getStrategyRowFromAdminTokenId(apiCustomResponse.getAdminTokenId());
    if ( row == -1 )
    {
        return;
    }
    int pId = getBaseWrapper()->getTableData(row,_iceBergParams->_portfolioId->getColumnIndex()).toLongLong();
    foreach ( std::string response, dataList )
    {
        keyValueList = QString::fromStdString(response).split(":"); //List of key and value.
        if ( keyValueList.size() == 2 )
        {
            key = keyValueList.at(0);
            value = keyValueList.at(1).toLongLong();
        }
        else
        {
            continue;
        }
        if ( key == QUANTITY )
        {
            sIdQtyNew = value;
        }
        else if ( key == TRADED_QUANTITY )
        {
            _tradedQuantity = value;
        }
        else if ( key == REMAINING_QUANTITY )
        {
            _remainingQuantity = value;
        }
    }
#if DEBUG
    std::cout<<getBaseWrapper()->getstrategyName().toStdString().c_str()<<std::endl;
    std::cout<<_iceBergParams->_adminTokenId->getParamName().toStdString().c_str()<<apiCustomResponse.getAdminTokenId()<<std::endl;
    std::cout<<"Total Quantity:"<<_totalQuantity<<std::endl;
    std::cout<<"REMAINING Quantity:"<<_remainingQuantity<<std::endl;
    std::cout<<"Traded quantity:"<<_tradedQuantity<<std::endl;
    std::cout<<"start Time:"<<_timer<<std::endl;
    std::cout<<_iceBergParams->_tradedQtyLegOne->getParamName().toStdString().c_str()<<std::endl;
#endif
    //UPDATE TRADED QUANTITY IN DATABASE
    QSqlQuery sqlQuery;
    sqlQuery.prepare("UPDATE "+getBaseWrapper()->getstrategyName() +" SET " + _iceBergParams->_tradedQtyLegOne->getParamName() + " = :" + _iceBergParams->_tradedQtyLegOne->getParamName() + " WHERE " + _iceBergParams->_adminTokenId->getParamName() + " = :" + _iceBergParams->_adminTokenId->getParamName());
    sqlQuery.bindValue(":" +  _iceBergParams->_tradedQtyLegOne->getParamName(),_tradedQuantity);
    sqlQuery.bindValue(":" + _iceBergParams->_adminTokenId->getParamName(),apiCustomResponse.getAdminTokenId());
    if ( !sqlQuery.exec() )
    {
        getBaseWrapper()->printSqlError(sqlQuery,__FILE__,Q_FUNC_INFO,__LINE__);
        return;
    }
    //total quantity need to be updated    total quantity = total quantity from ui +(total Quantity from Backup-SID from ui)
    long long sIdQtyOld = getBaseWrapper()->getTableData(row,_iceBergParams->_SIDTotalQty->getColumnIndex()).toLongLong();
    long long totalQuantity = getBaseWrapper()->getTableData(row,_iceBergParams->_totalQuantity->getColumnIndex()).toLongLong();
    long long diffTotalqty =sIdQtyNew-sIdQtyOld;
    totalQuantity+=diffTotalqty;
#if DEBUG
    std::cout<<"SID_QTY:"<<sIdQty<<std::endl;
    std::cout<<"totalQuantity:"<<totalQuantity<<std::endl;
    std::cout<<"DiffTotalqty"<<diffTotalqty<<std::endl;
    std::cout<<_iceBergParams->_totalQuantity->getParamName().toStdString().c_str()<<std::endl;
#endif
    //UPDATING TOTAL QUANTITY IN DATABASE
    sqlQuery.clear();
    sqlQuery.prepare("UPDATE "+getBaseWrapper()->getstrategyName()+" SET " + _iceBergParams->_totalQuantity->getParamName() + " =:" + _iceBergParams->_totalQuantity->getParamName() + " where " + _iceBergParams->_adminTokenId->getParamName() + " = :" + _iceBergParams->_adminTokenId->getParamName());
    sqlQuery.bindValue(":" + _iceBergParams->_totalQuantity->getParamName(),totalQuantity);
    sqlQuery.bindValue(":" + _iceBergParams->_adminTokenId->getParamName(),apiCustomResponse.getAdminTokenId());
    if ( !sqlQuery.exec() )
    {
        getBaseWrapper()->printSqlError(sqlQuery,__FILE__,Q_FUNC_INFO,__LINE__);
        return;
    }
    //UPDATING EVERY PARAMETER IN UI
    _baseTableModel->blockSignals(true);
    long long totalTraded = getTotalTradedQuantity(pId);
    getBaseWrapper()->setTableData(row,_iceBergParams->_SIDTotalQty->getColumnIndex(),sIdQtyNew);
    getBaseWrapper()->setTableData(row,_iceBergParams->_tradedQtyLegOne->getColumnIndex(),totalTraded);
    getBaseWrapper()->setTableData(row,_iceBergParams->_totalQuantity->getColumnIndex(),totalQuantity);
    getBaseWrapper()->setTableData(row,_iceBergParams->_remQty->getColumnIndex(),_remainingQuantity);
    QModelIndex index = getBaseWrapper()->getCurrentIndex();
    if ( index.isValid() )
    {
        int currentRow = index.row();
        if ( currentRow != -1 && currentRow == row )
        {
            ui->spinQuantity->setValue(totalQuantity);
        }
    }
    _baseTableModel->blockSignals(false);
}

long long Icebergui::getTotalTradedQuantity(long long pid)
{
    QSqlQuery query;
    QSqlRecord record;
    QString key = "SUM("+_iceBergParams->_tradedQtyLegOne->getParamName()+")";
    query.prepare("Select "+ key + " from "+getBaseWrapper()->getstrategyName()+" where "+ _iceBergParams->_portfolioId->getParamName() + "=:" + _iceBergParams->_portfolioId->getParamName());
    query.bindValue(":"+_iceBergParams->_portfolioId->getParamName(),pid);
    if ( !query.exec() )
    {
        getBaseWrapper()->printSqlError(query,__FILE__,Q_FUNC_INFO,__LINE__);
        return 0;
    }
    if ( query.next() )
    {
        record = query.record();
        return record.value(key).toLongLong();
    }
    return 0;
}

void Icebergui::initializeTabOrder()
{
    QComboBox* comboBoxSymbol = getBaseWrapper()->getSymbolCombo(API2::FIRST_LEG);
    setTabOrder(comboBoxSymbol,ui->comboSeries);
    setTabOrder(ui->comboSeries,ui->comboExpiry);
    setTabOrder(ui->comboExpiry,ui->comboOptMode);
    setTabOrder(ui->comboOptMode,ui->comboStrike);
    setTabOrder(ui->comboStrike,ui->lineEditLotSize);
    setTabOrder(ui->lineEditLotSize,ui->comboOrderType);
    setTabOrder(ui->comboOrderType,ui->comboFillType);
    setTabOrder(ui->comboFillType,ui->spinQuantity);
    setTabOrder(ui->spinQuantity,ui->doubleSpinLimitPrice);
    setTabOrder(ui->doubleSpinLimitPrice,ui->doubleSpinDisclosedPercent);
    setTabOrder(ui->doubleSpinDisclosedPercent,ui->spinDisclosedQuantity);
    setTabOrder(ui->spinDisclosedQuantity,ui->radioPro);
    setTabOrder(ui->radioPro,ui->radioClient);
    setTabOrder(ui->radioClient,ui->comboAccount);
    setTabOrder(ui->comboAccount,ui->lineEditPartCode);
    setTabOrder(ui->lineEditPartCode,getBaseWrapper()->getpushButton(API2::CTRL_BTN_NEW));
    setTabOrder(getBaseWrapper()->getpushButton(API2::CTRL_BTN_NEW),getBaseWrapper()->getpushButton(API2::CTRL_BTN_EDIT));
    setTabOrder(getBaseWrapper()->getpushButton(API2::CTRL_BTN_EDIT),getBaseWrapper()->getpushButton(API2::CTRL_BTN_COMMIT));
    setTabOrder(getBaseWrapper()->getpushButton(API2::CTRL_BTN_COMMIT),getBaseWrapper()->getpushButton(API2::CTRL_BTN_ADD));
    setTabOrder(getBaseWrapper()->getpushButton(API2::CTRL_BTN_ADD),getBaseWrapper()->getpushButton(API2::CTRL_BTN_REMOVE));
    setTabOrder(getBaseWrapper()->getpushButton(API2::CTRL_BTN_REMOVE),getBaseWrapper()->getpushButton(API2::CTRL_BTN_RUN));
    setTabOrder(getBaseWrapper()->getpushButton(API2::CTRL_BTN_RUN),getBaseWrapper()->getpushButton(API2::CTRL_BTN_STOPALL));
    setTabOrder(getBaseWrapper()->getpushButton(API2::CTRL_BTN_STOPALL),ui->pushButtonClose);
}

bool Icebergui::updateStrategyDefaultValues(qlonglong adminTokenIdNew)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("Update " + getBaseWrapper()->getstrategyName() + " set " + _iceBergParams->_tradedQtyLegOne->getParamName() + "=:" + _iceBergParams->_tradedQtyLegOne->getParamName() + " where " + _iceBergParams->_adminTokenId->getParamName()+"=:"+_iceBergParams->_adminTokenId->getParamName());
    sqlQuery.bindValue(":"+_iceBergParams->_adminTokenId->getParamName(),adminTokenIdNew);
    sqlQuery.bindValue(":"+_iceBergParams->_tradedQtyLegOne->getParamName(),0);
    if ( !sqlQuery.exec() )
    {
        getBaseWrapper()->printSqlError(sqlQuery);
    }
    return true;
}

void Icebergui::rowRemovedNotifier(int row,int pid)
{
    _pidSidQty.remove(pid);
}

void Icebergui::keyPressEvent(QKeyEvent * event)
{
    getBaseWrapper()->keyPressEvent(event);
}

void Icebergui::onAltSPressed()
{
    getBaseWrapper()->onSavePortFolio();
}

void Icebergui::onAltOPressed()
{
    getBaseWrapper()->onLoadPortFolioNew();
}

short Icebergui::getOrderMode(const QString & orderMode)
{
    if ( orderMode == BUY )
    {
        return order_Mode_BUY;
    }
    if ( orderMode == SELL )
    {
        return order_Mode_SELL;
    }
    return order_Mode_MAX;
}

QString Icebergui::getStrategyDisplayName()
{
    return "IceBerg";
}

void Icebergui::replacePortfolioValuesOnSave(QStringList &dataList)
{
    getBaseWrapper()->movePortfolioIndex(dataList,getBaseWrapper()->getClientCodePortfolioIndex(API2::FIRST_LEG),_iceBergParams->_symbolIdOne->getPortfolioIndex() + 1);
}

void Icebergui::replacePortfolioValuesOnLoad(QStringList &dataList)
{
    getBaseWrapper()->movePortfolioIndex(dataList,_iceBergParams->_symbolIdOne->getPortfolioIndex() + 1,getBaseWrapper()->getClientCodePortfolioIndex(API2::FIRST_LEG) + 2);
}

bool Icebergui::isNewState()
{
    ui->comboMode->isEnabled();
    return true;
}

bool Icebergui::isPortfolioNewLoadSaveHandling()
{
    return false;
}

//non-class function to return pointer to class
extern "C" __declspec(dllexport) void* createObject()
{
    Icebergui *ptr = &Icebergui::getInstance();
    return (void *)ptr;
}
