#include "bracketordergui.h"
#include "ui_bracketordergui.h"
#include "../../../FrontEnd_Api_Includes/dll_includes/StrategyConstants.h"

#define SYMBOL_ID           "SYMBOL LEG1"
#define ORDER_MODE          "Order Mode 1"
#define ACC_DETAIL          "Acc Detail 1"

#define ORDER_TYPE_LEG_1    "Order Type Leg1"
#define FILL_TYPE_LEG_1     "Fill Type Leg1"
#define QUANTITY_LEG_1      "Quantity Leg1"
#define LIMIT_PRICE_LEG_1   "Limit Price Leg1"
#define TRIGGER_PRICE_LEG_1 "Trigger Price Leg1"

#define ORDER_TYPE_LEG_2    "Order Type Leg2"
#define FILL_TYPE_LEG_2     "Fill Type Leg2"
#define QUANTITY_LEG_2      "Quantity Leg2"
#define LIMIT_PRICE_LEG_2   "Limit Price Leg2"
#define TRIGGER_PRICE_LEG_2 "Trigger Price Leg2"

#define ORDER_TYPE_LEG_3    "Order Type Leg3"
#define FILL_TYPE_LEG_3     "Fill Type Leg3"
#define QUANTITY_LEG_3      "Quantity Leg3"
#define LIMIT_PRICE_LEG_3   "Limit Price Leg3"
#define TRIGGER_PRICE_LEG_3 "Trigger Price Leg3"

#define fileName "Bracket Order"

BracketOrderGui::BracketOrderGui(QWidget *parent) :
    ui(new Ui::BracketOrderGui),
    _isNewStrategyWriteMethod(false)
{
    ui->setupUi(this);
}

BracketOrderGui::~BracketOrderGui()
{
    delete ui;
}

void BracketOrderGui::initDisplay()
{
    initialize();
    setWindowTitle(windowTitle() + " - Ver -" + getCommonMethodsWrapper()->getStrategyVersion());
    setWindowFlags( windowFlags() | Qt::WindowMinimizeButtonHint);
    initializeTabOrder();
    if(isHidden())
        show();
    else
        showNormal();
    raise();
    activateWindow();
}

void BracketOrderGui::initialize()
{
    _isNewStrategyWriteMethod = getBaseWrapper()->configFileValue("NEW_STRATEGY_WRITE_METHOD");
    populateElements();
    connect(&_timer, SIGNAL(timeout()), this, SLOT(updateDataOnTimer()));
    connect(ui->pushButtonClose,SIGNAL(clicked()),this,SLOT(onClosePushButtonClicked()));
    setDefaultIndex();
    ui->groupBox_4->setVisible(false);
    setConnections();
    _timer.start(800);
}

void BracketOrderGui::populateElements()
{
    populateStrategyParams();
    initializeSymbolPanel();
    _bracketorderparams = new BracketOrderParams(ui);
    _paramsMap = &_bracketorderparams->getParamList();
    ui->buttonPanel->addWidget(getBaseWrapper()->getButtonPanel());
    getBaseWrapper()->setStrategyContainer(ui->groupBoxShowHide,NULL);
    getBaseWrapper()->hideButtons(API2::CTRL_BTN_SETTINGS);
    getBaseWrapper()->hideButtons(API2::CTRL_BTN_STOPALL);
    getBaseWrapper()->hideButtons(API2::CTRL_BTN_MINIMIZE);
    getBaseWrapper()->addtoParamsGroup(_paramsMap);
    getBaseWrapper()->setStrategyInSingleRow(0);
    getBaseWrapper()->addToMainStrategyWindow(ui->tablePanel);
    getBaseWrapper()->setStrategyContainer(ui->groupBoxShowHide,ui->pushButtonClose);
    _baseTableModal = getBaseWrapper()->getTableModel();

}

void BracketOrderGui::initializeSymbolPanel()
{
    SymbolPanelElements *symbolPanelElements = new SymbolPanelElements(ui->orderComboBox, ui->sourceComboBox, ui->marketComboBox, ui->instrumentComboBox, ui->symbolVerticalLayout, ui->seriesComboBox, ui->expiryComboBox, ui->optModeComboBox, ui->strikeComboBox, ui->lotSizeLineEdit, ui->clientRadioButton, ui->proRadioButton, ui->partCodeLineEdit, ui->clientCodeComboBox);
    getBaseWrapper()->addSymbolPanel( API2::FUTURE | API2::STOCK | API2::OPTION, symbolPanelElements, true);
    ui->lotSizeLineEdit->setDisabled(true);
    getBaseWrapper()->initializeFirstLegSignals();
}

void BracketOrderGui::populateStrategyParams()
{
    QStringList order_types,fill_types,quantity_types;
    order_types<<"LIMIT"<<"MARKET";
    fill_types<<"DAY"<<"IOC";
    quantity_types<<"HALF"<<"FULL";

    ui->orderLeg1ComboBox->addItems(order_types);
    ui->orderLeg2ComboBox->addItems(order_types);
    ui->orderLeg3ComboBox->addItems(order_types);

    ui->fillLeg1ComboBox->addItems(fill_types);
    ui->fillLeg2ComboBox->addItems(fill_types);
    ui->fillLeg3ComboBox->addItems(fill_types);

    ui->quantityLeg2ComboBox->addItems(quantity_types);
    ui->quantityLeg3ComboBox->addItems(quantity_types);

    ui->modeLeg1LineEdit->setText("Buy");
    ui->modeLeg2LineEdit->setText("Sell");
    ui->modeLeg3LineEdit->setText("Sell");

    ui->modeLeg1LineEdit->setDisabled(true);
    ui->modeLeg2LineEdit->setDisabled(true);
    ui->modeLeg3LineEdit->setDisabled(true);
}

void BracketOrderGui::onAddPushButtonClicked()
{
    getBaseWrapper()->on_AddPushButton_Clicked();
}

void BracketOrderGui::onStopPushButtonClicked()
{
    getBaseWrapper()->on_StopPushButton_Clicked();
}

void BracketOrderGui::onStopAllPushButtonclicked()
{
    getBaseWrapper()->on_StopAllPushButton_clicked();
}

bool BracketOrderGui::buildCommandFromUi(API2::PORTFOLIO_STATE state)
{
    _bracketorderparams->_adminTokenId->setValue(0);
    _bracketorderparams->_clientId->setValue(getBaseWrapper()->getUserId());
    _bracketorderparams->_strategyId->setValue(0);
    _bracketorderparams->_riskStatus->setValue(API2::CONSTANTS::RSP_RiskStatus_MAX);
    _bracketorderparams->_portfolioId->setValue(getBaseWrapper()->getPortFolioId());
    _bracketorderparams->_state->setValue(API2::CONSTANTS::RSP_ResponseType_MAX);
    _bracketorderparams->_strategyComment->setValue(API2::CONSTANTS::RSP_StrategyComment_MAX);
    _bracketorderparams->_transactionType->setValue(API2::CONSTANTS::CMD_TransactionType_NEW);
    _bracketorderparams->_sequenceNumber->setValue(0);

    qlonglong symbolId = getBaseWrapper()->getLegsSymbolId(API2::FIRST_LEG);
    const API2:: SymbolDetail &sd = getBaseWrapper()->getSymbolIdDetail(symbolId);

    _bracketorderparams->_symbolId->setValue(symbolId);
    _bracketorderparams->_symbolName->setValue(sd.scripName);
    _bracketorderparams->_mode->setValue(ui->orderComboBox->currentIndex());

    _bracketorderparams->_orderTypeLeg1->setValue(ui->orderLeg1ComboBox->currentIndex());
    _bracketorderparams->_fillTypeLeg1->setValue(ui->fillLeg1ComboBox->currentIndex());
    _bracketorderparams->_quantityLeg1->setValue(ui->quantityLeg1SpinBox->value());
    _bracketorderparams->_limitPriceLeg1->setValue(ui->limitLeg1DoubleSpinBox->value()*100);
    _bracketorderparams->_triggerPriceLeg1->setValue(ui->triggerLeg1DoubleSpinBox->value()*100);
    _bracketorderparams->_orderTypeLeg2->setValue(ui->orderLeg2ComboBox->currentIndex());
    _bracketorderparams->_fillTypeLeg2->setValue(ui->fillLeg2ComboBox->currentIndex());
    _bracketorderparams->_quantityLeg2->setValue(ui->quantityLeg2ComboBox->currentText());
    _bracketorderparams->_limitPriceLeg2->setValue(ui->limitLeg2DoubleSpinBox->value()*100);
    _bracketorderparams->_triggerPriceLeg2->setValue(ui->triggerLeg2DoubleSpinBox->value()*100);
    _bracketorderparams->_orderTypeLeg3->setValue(ui->orderLeg3ComboBox->currentIndex());
    _bracketorderparams->_fillTypeLeg3->setValue(ui->fillLeg3ComboBox->currentIndex());
    _bracketorderparams->_quantityLeg3->setValue(ui->quantityLeg3ComboBox->currentIndex());
    _bracketorderparams->_limitPriceLeg3->setValue(ui->limitLeg3DoubleSpinBox->value()*100);
    _bracketorderparams->_triggerPriceLeg3->setValue(ui->triggerLeg3DoubleSpinBox->value()*100);

    return true;

}

void BracketOrderGui::setDefaultIndex()
{
    getBaseWrapper()->_col.adminTokenIdIndex    = _bracketorderparams->_adminTokenId->getColumnIndex();
    getBaseWrapper()->_col.stateIndex           = _bracketorderparams->_state->getColumnIndex();
    getBaseWrapper()->_col.strategyIdIndex      = _bracketorderparams->_strategyId->getColumnIndex();
    getBaseWrapper()->_col.strategyCommentIndex = _bracketorderparams->_strategyComment->getColumnIndex();
    getBaseWrapper()->_col.portFolioIdIndex     = _bracketorderparams->_portfolioId->getColumnIndex();
    getBaseWrapper()->_col.symbolIdLeg1         = _bracketorderparams->_symbolId->getColumnIndex();
}

void BracketOrderGui::setConnections()
{
    connect(ui->orderLeg1ComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(isOrderTypeChanged()));
    connect(ui->orderLeg2ComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(isOrderTypeChanged()));
    connect(ui->orderLeg3ComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(isOrderTypeChanged()));
    connect(ui->orderComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(isOrderTypeChanged()));
    connect(ui->marketComboBox,SIGNAL(activated(int)),this,SLOT(setPrecisionDecimal()));
}

void BracketOrderGui::isOrderTypeChanged()
{
    if(ui->orderLeg1ComboBox->currentText()=="MARKET")
    {
        ui->limitLeg1DoubleSpinBox->setDisabled(true);
        ui->limitLeg1DoubleSpinBox->setValue(0);
    }
    else
    {
        ui->limitLeg1DoubleSpinBox->setDisabled(false);
    }

    if(ui->orderLeg2ComboBox->currentText()=="MARKET")
    {
        ui->limitLeg2DoubleSpinBox->setDisabled(true);
        ui->limitLeg2DoubleSpinBox->setValue(0);
    }
    else
    {
        ui->limitLeg2DoubleSpinBox->setDisabled(false);
    }

    if(ui->orderLeg3ComboBox->currentText()=="MARKET")
    {
        ui->limitLeg3DoubleSpinBox->setDisabled(true);
        ui->limitLeg3DoubleSpinBox->setValue(0);
    }
    else
    {
        ui->limitLeg3DoubleSpinBox->setDisabled(false);
    }

    if(ui->orderComboBox->currentText() == "Buy")
    {
        ui->modeLeg1LineEdit->setText("Buy");
        ui->modeLeg2LineEdit->setText("Sell");
        ui->modeLeg3LineEdit->setText("Sell");
    }
    else
    {
        ui->modeLeg1LineEdit->setText("Sell");
        ui->modeLeg2LineEdit->setText("Buy");
        ui->modeLeg3LineEdit->setText("Buy");
    }
}

void BracketOrderGui::setPrecisionDecimal()
{
    qlonglong symbolId = getBaseWrapper()->getLegsSymbolId(API2::FIRST_LEG);
    const API2::SymbolDetail &sd  = getBaseWrapper()->getSymbolIdDetail(symbolId);
    if(!sd.flag)
        return;

    double stepsize = (double)sd.tickSize/sd.multiplier;
    ui->quantityLeg1SpinBox->setValue(sd.lotSize);

    ui->limitLeg1DoubleSpinBox->setDecimals(sd.precision);
    ui->limitLeg1DoubleSpinBox->setSingleStep(stepsize);
    ui->triggerLeg1DoubleSpinBox->setDecimals(sd.precision);
    ui->triggerLeg1DoubleSpinBox->setSingleStep(stepsize);

    ui->limitLeg2DoubleSpinBox->setDecimals(sd.precision);
    ui->limitLeg2DoubleSpinBox->setSingleStep(stepsize);
    ui->triggerLeg2DoubleSpinBox->setDecimals(sd.precision);
    ui->triggerLeg2DoubleSpinBox->setSingleStep(stepsize);

    ui->limitLeg3DoubleSpinBox->setDecimals(sd.precision);
    ui->limitLeg3DoubleSpinBox->setSingleStep(stepsize);
    ui->triggerLeg3DoubleSpinBox->setDecimals(sd.precision);
    ui->triggerLeg3DoubleSpinBox->setSingleStep(stepsize);
}

bool BracketOrderGui::isSpreadCalculationAllowed()
{
    return false;
}

void BracketOrderGui::updateSymbolIdsDetail(int row,bool isUpdateAll)
{
    if(row == -1) return;
    int start=row,end=row+1;

    if(isUpdateAll)
    {
        start = 0;
        end = _baseTableModal->rowCount();
        getBaseWrapper()->_hashRowSymboID.clear();
        getBaseWrapper()->_hashRowSpreadDetail.clear();
    }

    for(int counter=start;counter<end;counter++)
    {
        getBaseWrapper()->insertHashRowSymbolId(counter,
                                                _bracketorderparams->_symbolId->getColumnIndex(),
                                                _baseTableModal->item(counter,_bracketorderparams->_quantityLeg1->getColumnIndex())->data(Qt::DisplayRole).toLongLong());
    }
}

void BracketOrderGui::updateRemainingFeilds(int row, QSqlRecord &adminTokenIdData)
{
    getBaseWrapper()->setTableData(row,
                                   _bracketorderparams->_symbolName->getColumnIndex(),
                                   getBaseWrapper()->getScripName(adminTokenIdData.value(_bracketorderparams->_symbolId->getParamName()).toLongLong ()));

    getBaseWrapper()->setTableData(row,
                                   _bracketorderparams->_state->getColumnIndex(),
                                   getCommonMethodsWrapper()->getStrategyState(adminTokenIdData.value(_bracketorderparams->_state->getParamName()).toInt()));
}

void BracketOrderGui::onRemovePushButtonClicked()
{
    getBaseWrapper()->on_RemovePushButton_Clicked();
}

void BracketOrderGui::onNewPushButtonClicked()
{
    getBaseWrapper()->enableSymbolPanel(API2::FIRST_LEG, true);
    getBaseWrapper()->on_NewPushButton_Clicked();
}

void BracketOrderGui::onEditPushButtonClicked()
{
    QModelIndex index = getBaseWrapper()->getCurrentIndex();
    if(index.isValid())
    {
        getBaseWrapper()->on_EditPushButton_Clicked(index.row());
        getBaseWrapper()->enableSymbolPanel(API2::FIRST_LEG, false);
    }
}

void BracketOrderGui::onCommitPushButtonClicked()
{
    QModelIndex index = getBaseWrapper()->getCurrentIndex();
    if(!index.isValid()) return;

    getBaseWrapper()->on_CommitPushButton_Clicked();
}

bool BracketOrderGui::validateData(API2::PORTFOLIO_STATE state)
{
    if(!getBaseWrapper()-> validateData(API2::FIRST_LEG))
    {
        QMessageBox :: warning (this, fileName, "fill all parameter");
        return false;
    }
    if(ui->orderComboBox->currentText().isEmpty())
    {
        QMessageBox::warning(this,getBaseWrapper()->getFileName(),trUtf8("Invalid Order Type"));
        ui->orderComboBox->setFocus();
        getBaseWrapper()->resetWidgetStateOnValidation(state,_bracketorderparams->_mode);
        return false;
    }

    qlonglong symbolId = getBaseWrapper()->getLegsSymbolId(API2::FIRST_LEG);
    const API2:: SymbolDetail &sd = getBaseWrapper()->getSymbolIdDetail(symbolId);
    qlonglong quantityLeg1 = QString::number(ui->quantityLeg1SpinBox->value(),'f',sd.precision).remove(".").toLongLong();
    uint buy_sell = ui->orderComboBox->currentIndex();
    QString orderLeg1 = ui->orderLeg1ComboBox->currentText();
    QString orderLeg2 = ui->orderLeg2ComboBox->currentText();
    QString orderLeg3 = ui->orderLeg3ComboBox->currentText();
    qreal limitPriceLeg1 = ui->limitLeg1DoubleSpinBox->value();
    qreal triggerPriceLeg1 = ui->triggerLeg1DoubleSpinBox->value();
    qreal limitPriceLeg2 = ui->limitLeg2DoubleSpinBox->value();
    qreal triggerPriceLeg2 = ui->triggerLeg2DoubleSpinBox->value();
    qreal limitPriceLeg3 = ui->limitLeg3DoubleSpinBox->value();
    qreal triggerPriceLeg3 = ui->triggerLeg3DoubleSpinBox->value();

    if(!quantityLeg1){
         QMessageBox :: warning (this, fileName, "quantity can not be zero.");
         return false;
     }
    if(!limitPriceLeg1){
         QMessageBox :: warning (this, fileName, "limitPriceLeg1 can not be zero.");
         return false;
     }
    if(!limitPriceLeg2){
         QMessageBox :: warning (this, fileName, "limitPriceLeg2 can not be zero.");
         return false;
     }
    if(!limitPriceLeg3){
         QMessageBox :: warning (this, fileName, "limitPriceLeg3 can not be zero.");
         return false;
     }
    if(triggerPriceLeg1){
         QMessageBox :: warning (this, fileName, "triggerPriceLeg1 can not be zero.");
         return false;
     }
    if(triggerPriceLeg2){
         QMessageBox :: warning (this, fileName, "triggerPriceLeg2 can not be zero.");
         return false;
     }
    if(triggerPriceLeg3){
         QMessageBox :: warning (this, fileName, "triggerPriceLeg3 can not be zero.");
         return false;
     }

    if(buy_sell == 0)
    {
        if(orderLeg1 == "LIMIT" && triggerPriceLeg1 < limitPriceLeg1)
        {
            QMessageBox :: warning(this,fileName,"Trigger Price Leg1 must be greater than Limit Price Leg1");
            return false;
        }

        if(orderLeg2 == "LIMIT" && triggerPriceLeg2 < limitPriceLeg2)
        {
            QMessageBox :: warning(this,fileName,"Trigger Price Leg2 must be greater than Limit Price Leg2");
            return false;
        }

        if(orderLeg3 == "LIMIT" && triggerPriceLeg3 > limitPriceLeg3)
        {
            QMessageBox :: warning(this,fileName,"Limit Price Leg3 must be greater than Trigger Price Leg3");
            return false;
        }

        if(triggerPriceLeg3 < triggerPriceLeg2)
        {
            QMessageBox :: warning(this,fileName,"Trigger Price Leg3 must be greater than Trigger Price Leg2");
            return false;
        }

        if(triggerPriceLeg2 > triggerPriceLeg1)
        {
            QMessageBox :: warning(this,fileName,"Trigger Price Leg1 must be greater than Trigger Price Leg2");
            return false;
        }

        if(triggerPriceLeg3 < triggerPriceLeg1)
        {
            QMessageBox :: warning(this,fileName,"Trigger Price Leg3 must be greater than Trigger Price Leg1");
            return false;
        }
    }
    else
    {
        if(orderLeg1 == "LIMIT" && triggerPriceLeg1 > limitPriceLeg1)
        {
            QMessageBox :: warning(this,fileName,"Limit Price Leg1 must be greater than Trigger Price Leg1");
            return false;
        }

        if(orderLeg2 == "LIMIT" && triggerPriceLeg2 > limitPriceLeg2)
        {
            QMessageBox :: warning(this,fileName,"Limit Price Leg2 must be greater than Trigger Price Leg2");
            return false;
        }

        if(orderLeg3 == "LIMIT" && triggerPriceLeg3 < limitPriceLeg3)
        {
            QMessageBox :: warning(this,fileName,"Trigger Price Leg3 must be greater than Limit Price Leg3");
            return false;
        }

        if(triggerPriceLeg3 > triggerPriceLeg2)
        {
            QMessageBox :: warning(this,fileName,"Trigger Price Leg2 must be greater than Trigger Price Leg3");
            return false;
        }

        if(triggerPriceLeg2 < triggerPriceLeg1)
        {
            QMessageBox :: warning(this,fileName,"Trigger Price Leg2 must be greater than Trigger Price Leg1");
            return false;
        }

        if(triggerPriceLeg3 > triggerPriceLeg1)
        {
            QMessageBox :: warning(this,fileName,"Trigger Price Leg1 must be greater than Trigger Price Leg3");
            return false;
        }
    }

    return true;
}

void BracketOrderGui::setPortfolioDefaultValues(QStringList &portfolioRow)
{
    portfolioRow.replace(getBaseWrapper()->getDbIndex(_bracketorderparams->_quantityLeg1->getParamName()),"0");
    portfolioRow.replace(getBaseWrapper()->getDbIndex(_bracketorderparams->_limitPriceLeg1->getParamName()),"0");
    portfolioRow.replace(getBaseWrapper()->getDbIndex(_bracketorderparams->_triggerPriceLeg1->getParamName()),"0");
    portfolioRow.replace(getBaseWrapper()->getDbIndex(_bracketorderparams->_limitPriceLeg2->getParamName()),"0");
    portfolioRow.replace(getBaseWrapper()->getDbIndex(_bracketorderparams->_triggerPriceLeg2->getParamName()),"0");
    portfolioRow.replace(getBaseWrapper()->getDbIndex(_bracketorderparams->_limitPriceLeg3->getParamName()),"0");
    portfolioRow.replace(getBaseWrapper()->getDbIndex(_bracketorderparams->_triggerPriceLeg3->getParamName()),"0");
}

void BracketOrderGui::onClosePushButtonClicked()
{
    ui->pushButtonClose->setText(ui->groupBoxShowHide->isVisible() ? "+" : "-");
    ui->groupBoxShowHide->setVisible(!ui->groupBoxShowHide->isVisible());
}

void BracketOrderGui::onEscapePressed()
{
    getBaseWrapper()->onEscapePressed();
}

void BracketOrderGui::onCtrlSpacePressed()
{
    getBaseWrapper()->onCtrlSpacePressed();
}

void BracketOrderGui::onUpKeyPressed()
{
    getBaseWrapper()->onUpKeyPressed();
}

void BracketOrderGui::OnDownKeyPressed()
{
    getBaseWrapper()->OnDownKeyPressed();
}

void BracketOrderGui::onRunPushButtonClicked()
{
    QModelIndex index =  getBaseWrapper()->getCurrentIndex();
    if(index.isValid())
    {

        getBaseWrapper()->runStrategy(index.row());

    }
    getBaseWrapper()->updateTableView();
}

void BracketOrderGui::onAltSPressed()
{
    getBaseWrapper()->onSavePortFolio();
}

void BracketOrderGui::onAltOPressed()
{
    getBaseWrapper()->onLoadPortFolioNew();
}

void BracketOrderGui::onRemoveAllClicked()
{
    getBaseWrapper()->on_RemoveAll_Clicked();
}

void BracketOrderGui::receiveStrategyResponse(API2::Strategy &strategyResponse)
{
    QSharedPointer<API2::Strategy> strategyResponseSharedPtr = QSharedPointer<API2::Strategy>(new API2::Strategy(strategyResponse));
    getBaseWrapper()->receiveStrategyResponse(strategyResponseSharedPtr);
}

void BracketOrderGui::setApiCommand(API2::UserParams *apiParams, QSqlRecord &record, int stgCount, short type)
{
    getBaseWrapper()->setCommandCategory(API2::CONSTANTS::CMD_CommandCategory_API2_STRATEGY);
    qlonglong adminTokenId = record.value(_bracketorderparams->_adminTokenId->getParamName()).toLongLong();
    apiParams->setAdminTokenId(adminTokenId);
    apiParams->setSequenceNumber(0);
    apiParams->setClientId(getBaseWrapper()->getUserId());
    apiParams->setStrategyId(record.value(_bracketorderparams->_strategyId->getParamName()).toLongLong());
    apiParams->setTransactionType(type);
    apiParams->setStrategyVersion(0);

    apiParams->setValue(SYMBOL_ID,record.value(_bracketorderparams->_symbolId->getParamName()).toLongLong());
    apiParams->setValue(ORDER_MODE,TO_QT_COMPATIBLE_ASCII(record.value(_bracketorderparams->_mode->getParamName()).toChar()));
    apiParams->setValue(ACC_DETAIL,getBaseWrapper()->getAccountDetailFromDb(adminTokenId,API2::FIRST_LEG));

    apiParams->setValue(ORDER_TYPE_LEG_1,TO_QT_COMPATIBLE_ASCII(record.value(_bracketorderparams->_orderTypeLeg1->getParamName()).toChar()));
    apiParams->setValue(FILL_TYPE_LEG_1,TO_QT_COMPATIBLE_ASCII(record.value(_bracketorderparams->_fillTypeLeg1->getParamName()).toChar()));
    apiParams->setValue(QUANTITY_LEG_1,record.value(_bracketorderparams->_quantityLeg1->getParamName()).toLongLong());
    apiParams->setValue(LIMIT_PRICE_LEG_1,record.value(_bracketorderparams->_limitPriceLeg1->getParamName()).toLongLong());
    apiParams->setValue(TRIGGER_PRICE_LEG_1,record.value(_bracketorderparams->_triggerPriceLeg1->getParamName()).toLongLong());

    apiParams->setValue(QUANTITY_LEG_2,TO_QT_COMPATIBLE_ASCII( record.value(_bracketorderparams->_quantityLeg2->getParamName()).toChar()));
    apiParams->setValue(QUANTITY_LEG_3,TO_QT_COMPATIBLE_ASCII( record.value(_bracketorderparams->_quantityLeg3->getParamName()).toChar()));


    apiParams->setValue(ORDER_TYPE_LEG_2,TO_QT_COMPATIBLE_ASCII(record.value(_bracketorderparams->_orderTypeLeg2->getParamName()).toChar()));
    apiParams->setValue(FILL_TYPE_LEG_2,TO_QT_COMPATIBLE_ASCII(record.value(_bracketorderparams->_fillTypeLeg2->getParamName()).toChar()));
    apiParams->setValue(LIMIT_PRICE_LEG_2,record.value(_bracketorderparams->_limitPriceLeg2->getParamName()).toLongLong());
    apiParams->setValue(TRIGGER_PRICE_LEG_2,record.value(_bracketorderparams->_triggerPriceLeg2->getParamName()).toLongLong());

    apiParams->setValue(ORDER_TYPE_LEG_3,TO_QT_COMPATIBLE_ASCII(record.value(_bracketorderparams->_orderTypeLeg3->getParamName()).toChar()));
    apiParams->setValue(FILL_TYPE_LEG_3,TO_QT_COMPATIBLE_ASCII(record.value(_bracketorderparams->_fillTypeLeg3->getParamName()).toChar()));
    apiParams->setValue(LIMIT_PRICE_LEG_3,record.value(_bracketorderparams->_limitPriceLeg3->getParamName()).toLongLong());
    apiParams->setValue(TRIGGER_PRICE_LEG_3,record.value(_bracketorderparams->_triggerPriceLeg3->getParamName()).toLongLong());
}

void BracketOrderGui::populateUIPanels(int row, QSqlRecord &record, bool isNewState)
{
    if(row==-1)
    {
        return;
    }

    ui->orderLeg1ComboBox->setCurrentIndex(ui->orderLeg1ComboBox->findText(getOrderTypeStr(record.value(_bracketorderparams->_orderTypeLeg1->getParamName()).toInt())));
    ui->fillLeg1ComboBox->setCurrentIndex(ui->fillLeg1ComboBox->findText(getFillTpyeStr(record.value(_bracketorderparams->_fillTypeLeg1->getParamName()).toInt())));
    ui->quantityLeg1SpinBox->setValue(record.value(_bracketorderparams->_quantityLeg1->getParamName()).toLongLong());
    ui->limitLeg1DoubleSpinBox->setValue(record.value(_bracketorderparams->_limitPriceLeg1->getParamName()).toLongLong()/100);
    ui->triggerLeg1DoubleSpinBox->setValue(record.value(_bracketorderparams->_triggerPriceLeg1->getParamName()).toLongLong()/100);

    ui->orderLeg2ComboBox->setCurrentIndex(ui->orderLeg2ComboBox->findText(getOrderTypeStr(record.value(_bracketorderparams->_orderTypeLeg2->getParamName()).toInt())));
    ui->fillLeg2ComboBox->setCurrentIndex(ui->fillLeg2ComboBox->findText(getFillTpyeStr(record.value(_bracketorderparams->_fillTypeLeg2->getParamName()).toInt())));
    ui->quantityLeg2ComboBox->setCurrentIndex(ui->quantityLeg2ComboBox->findText(getQuantityType(record.value(_bracketorderparams->_quantityLeg2->getParamName()).toInt())));
    ui->limitLeg2DoubleSpinBox->setValue(record.value(_bracketorderparams->_limitPriceLeg2->getParamName()).toLongLong()/100);
    ui->triggerLeg2DoubleSpinBox->setValue(record.value(_bracketorderparams->_triggerPriceLeg2->getParamName()).toLongLong()/100);

    ui->orderLeg3ComboBox->setCurrentIndex(ui->orderLeg3ComboBox->findText(getOrderTypeStr(record.value(_bracketorderparams->_orderTypeLeg3->getParamName()).toInt())));
    ui->fillLeg3ComboBox->setCurrentIndex(ui->fillLeg3ComboBox->findText(getFillTpyeStr(record.value(_bracketorderparams->_fillTypeLeg3->getParamName()).toInt())));
    ui->quantityLeg3ComboBox->setCurrentIndex(ui->quantityLeg3ComboBox->findText(getQuantityType(record.value(_bracketorderparams->_quantityLeg3->getParamName()).toInt())));
    ui->limitLeg3DoubleSpinBox->setValue(record.value(_bracketorderparams->_limitPriceLeg3->getParamName()).toLongLong()/100);
    ui->triggerLeg3DoubleSpinBox->setValue(record.value(_bracketorderparams->_triggerPriceLeg3->getParamName()).toLongLong()/100);

    if(!isNewState)
    {
        getBaseWrapper()->populateLeg(API2::FIRST_LEG,record.value(_bracketorderparams->_symbolId->getParamName()).toLongLong(),record.value(_bracketorderparams->_adminTokenId->getParamName()).toLongLong());
    }
}

void BracketOrderGui::updateEditableFieldColor(int row, QColor color)
{
    getBaseWrapper()->setColumnBackGround(row,_bracketorderparams->_quantityLeg1->getColumnIndex(),color);
    getBaseWrapper()->setColumnBackGround(row,_bracketorderparams->_limitPriceLeg1->getColumnIndex(),color);
    getBaseWrapper()->setColumnBackGround(row,_bracketorderparams->_triggerPriceLeg1->getColumnIndex(),color);
    getBaseWrapper()->setColumnBackGround(row,_bracketorderparams->_limitPriceLeg2->getColumnIndex(),color);
    getBaseWrapper()->setColumnBackGround(row,_bracketorderparams->_triggerPriceLeg2->getColumnIndex(),color);
    getBaseWrapper()->setColumnBackGround(row,_bracketorderparams->_limitPriceLeg3->getColumnIndex(),color);
    getBaseWrapper()->setColumnBackGround(row,_bracketorderparams->_triggerPriceLeg3->getColumnIndex(),color);
}

QString BracketOrderGui::getOrderTypeStr(const int &orderType)
{
    switch(orderType)
    {
    case order_Type_LIMIT:
        return "LIMIT";
    case order_Type_MARKET:
        return "MARKET";
    }
    return STRATEGY_CONST::UNKNOWNSTR;
}

QString BracketOrderGui::getFillTpyeStr(unsigned short orderValidity)
{
    switch(orderValidity)
    {
        case fill_Type_DAY:
            return getCommonMethodsWrapper()->getOrderValidityStr(fill_Type_DAY);
        case fill_Type_IOC:
            return getCommonMethodsWrapper()->getOrderValidityStr(fill_Type_IOC);
    }
    return STRATEGY_CONST::UNKNOWNSTR;
}

QString BracketOrderGui::getQuantityType(const int &quantityType)
{
    switch(quantityType)
    {
        case quantity_Type_Half:
            return "HALF";
        case quantity_Type_Full:
            return "FULL";
    }
    return STRATEGY_CONST::UNKNOWNSTR;
}

void BracketOrderGui::updateDataOnTimer()
{
    bool  _isNewStrategyWriteMethod = getBaseWrapper()->configFileValue("NEW_STRATEGY_WRITE_METHOD");
    if(!_isNewStrategyWriteMethod)
    {
        while(!getBaseWrapper()->_responseQueue.isEmpty())
        {
            getBaseWrapper()->updateResponse(getBaseWrapper()->_responseQueue.dequeue());
            if(_updateCounter++==8){
                break;
            }
        }
    }
    if(!getBaseWrapper()->isProcessingEvent())
        getBaseWrapper()->updateTableView();
}

void BracketOrderGui::initializeTabOrder()
{
    QComboBox* comboBoxSymbol = getBaseWrapper()->getSymbolCombo(API2::FIRST_LEG);
    setTabOrder(comboBoxSymbol,ui->seriesComboBox);
    setTabOrder(ui->seriesComboBox,ui->expiryComboBox);
    setTabOrder(ui->expiryComboBox,ui->optModeComboBox);
    setTabOrder(ui->optModeComboBox,ui->strikeComboBox);
    setTabOrder(ui->strikeComboBox,ui->lotSizeLineEdit);
    setTabOrder(ui->lotSizeLineEdit,ui->proRadioButton);
    setTabOrder(ui->proRadioButton,ui->clientRadioButton);
    setTabOrder(ui->clientRadioButton,ui->clientCodeComboBox);
    setTabOrder(ui->clientCodeComboBox,ui->orderLeg1ComboBox);
    setTabOrder(ui->orderLeg1ComboBox,ui->fillLeg1ComboBox);
    setTabOrder(ui->fillLeg1ComboBox,ui->quantityLeg1SpinBox);
    setTabOrder(ui->quantityLeg1SpinBox,ui->limitLeg1DoubleSpinBox);
    setTabOrder(ui->limitLeg1DoubleSpinBox,ui->triggerLeg1DoubleSpinBox);
    setTabOrder(ui->triggerLeg1DoubleSpinBox,ui->orderLeg2ComboBox);
    setTabOrder(ui->orderLeg2ComboBox,ui->fillLeg2ComboBox);
    setTabOrder(ui->fillLeg2ComboBox,ui->quantityLeg2ComboBox);
    setTabOrder(ui->quantityLeg2ComboBox,ui->limitLeg2DoubleSpinBox);
    setTabOrder(ui->limitLeg2DoubleSpinBox,ui->triggerLeg2DoubleSpinBox);
    setTabOrder(ui->triggerLeg2DoubleSpinBox,ui->orderLeg3ComboBox);
    setTabOrder(ui->orderLeg3ComboBox,ui->fillLeg3ComboBox);
    setTabOrder(ui->fillLeg3ComboBox,ui->quantityLeg3ComboBox);
    setTabOrder(ui->quantityLeg3ComboBox,ui->limitLeg3DoubleSpinBox);
    setTabOrder(ui->limitLeg3DoubleSpinBox,ui->triggerLeg3DoubleSpinBox);
    setTabOrder(ui->triggerLeg3DoubleSpinBox,getBaseWrapper()->getpushButton(API2::CTRL_BTN_NEW));
    setTabOrder(getBaseWrapper()->getpushButton(API2::CTRL_BTN_NEW),getBaseWrapper()->getpushButton(API2::CTRL_BTN_EDIT));
    setTabOrder(getBaseWrapper()->getpushButton(API2::CTRL_BTN_EDIT),getBaseWrapper()->getpushButton(API2::CTRL_BTN_COMMIT));
    setTabOrder(getBaseWrapper()->getpushButton(API2::CTRL_BTN_COMMIT),getBaseWrapper()->getpushButton(API2::CTRL_BTN_ADD));
    setTabOrder(getBaseWrapper()->getpushButton(API2::CTRL_BTN_ADD),getBaseWrapper()->getpushButton(API2::CTRL_BTN_REMOVE));
    setTabOrder(getBaseWrapper()->getpushButton(API2::CTRL_BTN_REMOVE),getBaseWrapper()->getpushButton(API2::CTRL_BTN_RUN));
    setTabOrder(getBaseWrapper()->getpushButton(API2::CTRL_BTN_RUN),getBaseWrapper()->getpushButton(API2::CTRL_BTN_STOPALL));
    setTabOrder(getBaseWrapper()->getpushButton(API2::CTRL_BTN_STOPALL),ui->pushButtonClose);

}

bool BracketOrderGui::isPortfolioNamePresent()
{
    return false;
}

bool BracketOrderGui::isSidTotalQtyHandling()
{
    return false;
}

bool BracketOrderGui::isNewState()
{
    ui->orderComboBox->isEnabled();
    return true;
}

void BracketOrderGui::getDllVersionString(QString &dllVersionString)
{
    dllVersionString = DLL_VERSION_STRING;
}

extern "C" __declspec(dllexport) void* createObject()
{
    BracketOrderGui *ptr = new BracketOrderGui();
    return (void *)ptr;
}

bool BracketOrderGui::isStrategyLegPresent()
{
    return false;
}
