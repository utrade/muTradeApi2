#ifndef BASESTRATEGYWRAPPER_H
#define BASESTRATEGYWRAPPER_H

#include "sharedParams.h"
#if IS_QT4_VERSION
#include <QShortcut>
#else
#include <QtWidgets/QShortcut>
#endif
#include "sharedStrutures.h"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlRecord"
#define Unknownstr "Unknown"
#ifndef MUTRADE_CLIENT
#include "../../api2/api_includes/api2RequestResponse.h"
#include "../../api2/api_includes/sharedResponse.h"
#include "../../api2/api_includes/api2UserCommands.h"
#else
#include "../api2/headers/api2UserCommands.h"
#include "api2/headers/api2RequestResponse.h"
#include "shared/response.h"
#endif

class APIWrapper;
class CommonMethodsWrapper;
class BaseStrategyWrapper : public QDialog
{
    Q_OBJECT
public:
    ColumnIndex _col;
    QHash<int ,QList<BaseSymbolIds*> > _hashRowSymboID;
    QQueue<QSharedPointer<API2::Strategy> > _responseQueue;
    QHash<int ,SpreadDetails*> _hashRowSpreadDetail;

    explicit BaseStrategyWrapper(){}
    ~BaseStrategyWrapper(){}
    APIWrapper *_ApiPointer;
    void setApiPointer(APIWrapper *ptr){_ApiPointer=ptr;}


    virtual bool isProcessingEvent(){ return false; }
    virtual void initialize(){}
    virtual bool isDisplayInLots() { return false; }
    virtual void setMarketAndSecurityId(qlonglong symbolId){}
    virtual QStandardItemModel *getTableModel(){ return NULL; }
    virtual void setRatioChecked(bool ratio){}
    virtual void setStrategyContainer(QGroupBox *strategyContainer,QPushButton *showHideLegPushButton){}
    virtual void populateOrderType(QComboBox *orderType){}
    virtual void populateBiddingLeg(QComboBox * comboBoxBiddingLong,short legCount){}
    virtual void populateHedgeMethods(QComboBox *comboBoxHedgeMethod, bool isActualDiffAllowed=false){}
    virtual void populateBaseSpread(QComboBox *baseSpread){}
    virtual void populateSpreadType(QComboBox *comboSpreadType){}
    virtual void populateExecutionStyle(QComboBox *comboSpreadType){}
    virtual int  getDbIndex(const QString name){ return -1; }
    virtual void addtoParamsGroup(API2::StrategyParamMap *paramMap){}
    virtual bool isPushButtonEnabled(short button){ return false; }
    virtual QGroupBox* getButtonPanel(){ return NULL; }
    virtual QPushButton* getpushButton(short button){ return NULL; }
    virtual void populateSpreadTerm(QComboBox *spreadTerm){}

    /** ------------ Getters --------------- **/
    virtual qlonglong getPortFolioId() { return -1; }
    virtual QString getPortFolioName() { return ""; }
    virtual QString getstrategyName() { return ""; }
    virtual QString getLegTypeStr(short leg){ return ""; }
    virtual API2::LEGS getLegType(QString str){ return API2::LEG_MAX; }
    virtual void addToMainStrategyWindow(QVBoxLayout *tableviewLayout){}
    virtual void addSymbolPanel(const short instrument,SymbolPanelElements *elements,bool isExpiry,bool addExchanges=true){}
    virtual QVariant getTableData(int row,int col){ return QVariant(); }
    virtual  bool isStrategyReadyState(){ return false; }


    /** ------------------- Setters ------------- **/
    virtual void onLoadOldStrategies(){}
    virtual void runStrategy(int row = -1, bool isWriteMethod=false, bool isModifyFromAltM=false){}
    virtual void insertHashRowSymbolId(int row,
                                       int symbolIdIndex,
                                       qlonglong quantity,
                                       int orderModeIndex,
                                       short strategyType,
                                       qlonglong underlyingSymbolId = 0){}
    virtual void insertHashRowSymbolId(BaseSymbolIds *symbolIds,
                                       int row,
                                       int symbolIdIndex,
                                       qlonglong quantity,
                                       int orderModeIndex,
                                       short strategyType,
                                       qlonglong underlyingSymbolId = 0){}
    virtual void insertHashRowSymbolId(int row,
                                       int symbolIdIndex,
                                       qlonglong quantity) {}
    virtual void restoreTableHeaderState(){}
    virtual void updateTableView(){}
    virtual bool checkForUnderLying(){return true;}
    virtual void onRemoveAllClicked(){}
    virtual void setTableData(int row,int col,QVariant data){}
    virtual void setColumnBackGround(int row,int colIndex,QColor color){}
    virtual void setStrategyInSingleRow(short count){}
    virtual void disableColumn(QStandardItem *item, bool isDefaultColor = true){}
    virtual void updateSpreadInPortfolio(){}
    virtual void addDefaultParameter(QString name,short type,QWidget *element, QWidget *elementGroup = 0){}
    virtual void addNewSectionDefaultSetting(QString containerName){}

    //// DVM
    virtual void resetData(QString str,QComboBox *combo){}
    virtual void loadDeafaultValuseFromFile(){}
    virtual void applyDefaultValues(const QStringList& ignoredkey = (QStringList() << Unknownstr)){}
    virtual void applyDefaultValue(QString){}
    virtual void setDVMFocusWiget(QString focusWidgetKey){}
    virtual void closeDefaultManager(){}
    virtual void setDefaultValuesHash(QHash<QString, QString> &defaultValuesMap){}


    ///symbolPanel
    virtual void setSymbolToolTip(API2::LEGS leg,const char *tooltip){}
    virtual void setItmStatus(bool itmStatue){}
    virtual qlonglong getLegsSymbolId(API2::LEGS leg){ return 0; }
    virtual void populateSymbolPRO(API2::LEGS leg,qlonglong symbolId){}
    virtual void populateAccountDetail(API2::LEGS leg,qlonglong symbolId){}
    virtual void enableSymbolPanel(API2::LEGS leg,bool isEnable,bool isAccountDetail = true, bool isNewButtonClicked = true){}
    virtual QString getCurrentSymbol(API2::LEGS leg){ return ""; }
    virtual QString getCurrentExpiry(API2::LEGS leg){ return ""; }
    virtual void enableAccountDetailUI(API2::LEGS leg,bool status){}
    virtual void onComboBoxOptTypeActivated(short leg,QString arg){}
    virtual QString getCurrentMarket(API2::LEGS leg){ return ""; }
    virtual void showHidePanel(API2::LEGS leg,bool status){}
    virtual void setSymbol(API2::LEGS leg,QString symbol){}
    virtual bool validateData(API2::LEGS leg){ return false; }
    virtual void disabledFeilds(API2::LEGS leg,API2::SYM_PANEL element){}
    virtual void hideFeilds(API2::LEGS leg,API2::SYM_PANEL element){}
    virtual void clearLegDetails(API2::LEGS leg){}
    virtual void setCurrentInstrument(short leg, const QString& inst,bool isBlockSignal = false){}
    virtual void setCurrentInstrument(short leg, int index,bool isBlockSignal = false){}
    virtual QString getCurrentInstrument(short leg){ return ""; }
    virtual void setCurrentStrike(short leg, const QString& strike,bool isBlockSignal = false){}
    virtual void setCurrentStrike(short leg, int index,bool isBlockSignal = false){}
    virtual QString getCurrentStrike(short leg){ return ""; }
    virtual void setCurrentOptType(short leg, short index,bool isBlockSignal = false){}
    virtual QString getCurrentOptType(short leg){ return ""; }
    virtual void setCurrentOrderMode(short leg, short index,bool isBlockSignal = false){}
    virtual int getCurrentLotSize(short leg){return API2::LEG_MAX;}
    virtual void enableDisableOptType(short leg,bool isEnable){}
    virtual void enableDisableStrikePrice(short leg,bool isEnable){}

    ///CommonTableView
    virtual QComboBox* getFilterWidgetComboBox(int index){ return NULL; }
    virtual QModelIndex getCurrentIndex(){ return QModelIndex(); }
    virtual QModelIndex getProxyModelIndex(){ return QModelIndex(); }
    virtual bool isEditableColumn(int column){ return false; }
    virtual void setDelegateStepSize(double stepSize,short elementType, short decimals=2){}
    virtual void setDelegateMinValue(double minval,short elementType){}

    virtual void edit(QModelIndex &index){}
    virtual int  getRowCount(){ return -1; }
    virtual void setFocus(){}
    virtual void getEditableFieldData(qlonglong adminTokenId,QSqlRecord &records){}

    ///CommonMethods
    virtual qlonglong getCashSymbolId(QString source,QString market, QString symbol){ return 0; }
    virtual qlonglong getFutureSymbolId(QString source,QString market, QString symbol, QString strDate){ return 0; }
    virtual qlonglong getOptionSymbolId(QString source,QString market, QString symbol, QString strDate,QString optionType,QString strikePrice){ return 0; }
    virtual qlonglong getUnderlyingFutSymbolId(qlonglong symbolId){ return 0; }
    virtual QString maturityDayMonYearToString(int day, int yearMon){ return ""; }
    virtual void sortExpiryDate(QStringList expDateList,QStringList &sortedExpDateList){}

    virtual void convertExpiryToMonStr(QString &expiry){}
    virtual void convertExpiryToMonNumber(QString &expiry){}
    virtual void  getPrecisionAndMultiplier(qlonglong symbolId, double &multiplier, short &precision){}
    virtual double getPriceMultiplier(qlonglong symbolId){ return 0; }
    virtual QString getScripName(qlonglong symbolId){ return ""; }
    virtual void printSqlError(QSqlQuery &query){}
    virtual void printSqlError(QSqlQuery &query, QString fileName, QString funcName, int line){}
    virtual short configFileValue(const char *str){ return -1; }
    virtual QString configFileValueStr(const char *str){ return ""; }
    virtual QString getFileName(){ return ""; }
    virtual const API2::SymbolDetail& getSymbolIdDetail(qlonglong symbolId){ return API2::SymbolDetail(); }
    virtual qlonglong getUserId(){ return -1; }
    virtual void writeOnSocket(char *buffer, qint64 bytes, qint64 &bytesWritten){}
    virtual void getAccountDetailList(qlonglong adminTokenId,QList<qlonglong> &symbolIdList,QStringList &cCodePCodeList){}
    virtual qlonglong getLastLogOutTime(){return 0;}
    //Used for hiding and showing SHOW/HIDE widget
    virtual void hideShowCommonButtonPanelWidgets(API2::CTRL_BTN hideShowCheckBox,bool isShowHide){}

    //Market Data
    virtual qlonglong getLastTradePrice(qlonglong symbolId){ return -1; }
    virtual qlonglong getVolume(qlonglong symbolId){ return -1; }

    //AccountDetail
    virtual void updateAccountDetail(const int row){}
    virtual void updateAccountDetailOnEdit(const int row,const int col , API2::LEGS leg){}
    virtual bool isKeyExists(QString clientCode, qlonglong symbolId){ return false; }
    virtual API2::AccountDetail getAccountDetailFromDb(qlonglong adminTokenId,short leg){ return API2::AccountDetail(); }
    virtual void updateResponse(QSharedPointer<API2::Strategy> strategyResponseSharedPtr){}
    virtual SpreadDetails *getSpreadDetail(int row){ return NULL; }
    virtual bool getBidAsk(qlonglong symbolId, qlonglong& bidPrice, qlonglong &askPrice,int position=0){ return false; }
    virtual qlonglong getBidAskQty(qlonglong symbolId, const short &side, int position=0) { return 0;}

    virtual void getIvOrVegaVal( qlonglong symbolId,
                                 qlonglong &bidIv,
                                 qlonglong &askIv,
                                 short mode,
                                 double &bidVega,
                                 double &askVega,
                                 bool calculateVega,
                                 qlonglong underlyingSymbolId){}

    virtual void getIvVegaPrice(qlonglong symbolId,
                         qlonglong price,
                         short,
                         qlonglong underlyingSymbolId,
                         qlonglong &ivPrice,
                         double &vega,
                         bool isVegaCalculate){}

    virtual void onEscapePressed(){}
    virtual void onRunActivated(){}
    virtual void onCtrlSpacePressed(){}
    virtual void onUpKeyPressed(){}
    virtual void OnDownKeyPressed(){}
    virtual void insertTradeWiseTrackerList(QSharedPointer< API2::TradeWiseTrackerData> &tradeWiseTrackerData){}
    virtual void updateStrategyState(int row){}
    virtual int  getStrategyRowFromAdminTokenId(const qlonglong &adminTokenId){ return -1; }
    virtual int  getPortFolioRowFromPortfolioId(const qlonglong &portID){ return -1; }
    virtual void setCommandCategory(COMMAND_CATEGORY_TYPE){}
    virtual COMMAND_CATEGORY_TYPE getCommandCategory(){ return API2::CONSTANTS::CMD_CommandCategory_MAX; }
    virtual void receiveApiResponse(const API2::API2_Response &api2_Response){}
    virtual void modifyCancelOrders(qlonglong strategyId, API2::apiOrderBookParams *apiBookParams=NULL){}
    virtual QString getStrategyState(int row){ return ""; }
    virtual void hideButtons(API2::CTRL_BTN btn){}
    virtual void hideShowColumns(QTableView *tableView,
                         QString title,
                         QList<int>,
                         QWidget* parent,
                         bool isColumn,
                         QStandardItemModel *model){}
    virtual void addWidgetInButtonPanelGroup(QWidget*){}
    virtual void setEditableModeRow(int row){}
    virtual bool isShowHideTradedQtyChecked(){ return false; }

    //Unique Spread
    virtual bool validateUniqueSpreadCheckEntry(const QString &uniqueKey,const QString &spreadKey,bool isModify, bool showPopup =  true){ return false; }
    virtual void insertNewUniqueSpreadCheckEntry(const QString &uniqueKey,const QString &spreadKey){}
    virtual void removeUniqueSpreadKeyValue(const QString &uniqueKey,const QString &spreadKey){}
    virtual void clearUniqueSpreadPairs(){}
    virtual QPair<QString,QString> &getUniqueSpreadKeyValuePair(bool isNew = false){
        QPair<QString,QString> emptyPair(QString(""), QString(""));
        return emptyPair;
    }
    virtual void setCurrentSpreadKeyValuePair(const QString &key,const QString &value){}

    virtual int getFieldCount(){ return -1; }
    virtual void subscribeSymbol(qlonglong symbolId){}

    virtual bool isProcessingDefaultValues() { return false; }
    virtual double getGammaValue(qlonglong symbolId){ return 0; }
    virtual void checkShowHideQuantity(){}
    virtual QString getCmFoMarket(QString currentMarketId){ return ""; }
    virtual bool isSpotMarket(QString currentMarketId){ return false; }

    virtual int getEditableModeRow(){ return -1; }
    virtual void setIsSpreadPopAlreadyShown(bool isEnable){}

    virtual void enableNewPushButton(bool isEnable){}
    virtual bool isTableViewFocused(){ return false; }
    virtual void convertExpiryDate(QComboBox *comboBox){}
    // initialize Signals
    virtual void initializeFirstLegSignals(){}
    virtual void initializeSecondLegSignals(){}
    virtual void initializeThirdLegSignals(){}
    virtual void initializeFourthLegSignals(){}
    virtual void initializeHedgeLegSignals(){}
    virtual void keyPressEvent(QKeyEvent *event){}
    virtual void getOfflineConfirmationMap(QHash<QString, RSP::OrderConfirmation*> &orderBookConfirmationMap){}
    virtual QString getOrderStatus(short orderStatus){ return ""; }
    virtual QComboBox* getSymbolCombo(API2::LEGS leg){ return NULL; }
    virtual void onComboSymbolActivated(const QString &symbol,API2::LEGS leg){}
    virtual void onComboSymbolLostFocus(API2::LEGS leg){}
    virtual void resetWidgetStateOnValidation(API2::PORTFOLIO_STATE state,API2::PARAM *strategyParam,int lotSize = 1){}
    virtual void updateSqlRecordOnEdit(int row){}
    virtual QSqlQuery &fillDetailsFromAdminTokenId(const UNSIGNED_LONG adminTokenId,QString condition){QSqlQuery query;
                                                                                                      return query;}
    virtual void getGtcOrderConfirmationVector(QVector <RSP::OrderConfirmation*> &orderConfirmationVector){}
    virtual bool isGtcOrder(short orderValidity){return false;}
    virtual void setLastLogOutTime(qlonglong time){}
    virtual double getGreeksDelta(qlonglong symbolId){ return 0; }
    virtual bool getIsLoadFromMarketWatch(){ return false; }
    virtual bool isSymbolPanelInitialized(API2::LEGS leg){ return false; }
    virtual bool isSenderLeg(API2::LEGS leg,QObject *object){ return false; }
    virtual void processMktData(qlonglong symbolId){}

    virtual void symbolActivated(API2::LEGS leg){}
    virtual void setSpreadPopOnAddPortfolio(bool flag){}
    virtual void setDelegatesFocusOut(){}
    virtual bool validateAccountDetailOnLoad(const QString &clientCode , qlonglong symbolId){return false;}

    virtual void getAccountDetailFromPortfolio(API2::LEGS leg,const QStringList &dataList,QString &accountDetail){}
    virtual bool isModifyState(){ return false; }
    virtual bool isUnderLyingStock()
    {
        return false;
    }
    virtual void runAllStrategy(){}

    virtual bool isEditState(){ return false; }
    virtual int getClientCodePortfolioIndex(API2::LEGS leg) { return -1; }
    virtual void movePortfolioIndex(QStringList &dataList, int fromIndex, int toIndex) { }
    virtual void populateLeg(API2::LEGS leg, qlonglong symbolId,qlonglong adminTokenId){}


public slots:
    virtual void on_NewPushButton_Clicked() {}
    virtual bool on_AddPushButton_Clicked() { return false; }
    virtual void on_EditPushButton_Clicked(int row=-1){}
    virtual void setCurrentIndexFromRow(int row){}
    virtual void on_CommitPushButton_Clicked(bool isModifyFromAltM = false){}
    virtual void on_StopAllPushButton_clicked(){}
    virtual bool terminateStrategy(int row,int index = -1) {return false;}
    virtual void on_RemovePushButton_Clicked(){}
    virtual void on_StopPushButton_Clicked(){}
    virtual void on_RemoveAll_Clicked(){}
    virtual void onSettingPushButtonClicked() {}
    virtual bool populateStrategyFromPortfolio(){return true;}
    virtual void setItrationQty(API2::Strategy strategyResponse){}
    virtual void receiveStrategyResponse(QSharedPointer<API2::Strategy> strategyResponseSharedPtr){}
    virtual void setOldPositionUploadAllowed(bool isOldPositionUpload){}
    virtual bool getIsOldPositionUploadAllowed(){return false;}
    virtual bool getIsSpreadPopAlreadyShown(){return false;}
    virtual void setOptionsConRevCombination(QString conRevCombination){}
    virtual void onSavePortFolio(){}
    virtual void onLoadPortFolioNew(){}
    virtual API2::AbstractUserParams * getParamsCommand(){return NULL;}

    virtual QString getOptionsConRevCombination(){ return "" ; }

    virtual API2::AbstractUserParams * getNewParamsCommand(){return NULL;}
    virtual void deleteParamsCommand(API2::AbstractUserParams *&genericPtr){}
    virtual void serializeParamsCommand(API2::AbstractUserParams *genericPtr){}

    virtual void populateHedgingPortfolio(QComboBox * comboBox){}
    virtual void registerForUhedgePortfolio(){}
    virtual int getUhedgePortfolioId(const QString & portfolioName){return -1;}
    virtual const QString & getUhedgePortfolioNameFromId(const int portfolioId){return QString("");}
    virtual void updateStrategyVsUhedgePortfolioMap(long strategyId ,const QString & uhedgePortfolioName){}
	virtual int getPortfolioFieldCount(){ return 0 ; }
    virtual void onModifyStrategy(){}

};



class APIWrapper : public QDialog
{
    Q_OBJECT
    BaseStrategyWrapper *_baseStrategyWrapper;
    CommonMethodsWrapper *_commonMethodsWrapper;
public:

    void setBaseWrapper(BaseStrategyWrapper *baseStrategyWrapper)
    {
        _baseStrategyWrapper =  baseStrategyWrapper;
    }

    BaseStrategyWrapper* getBaseWrapper()
    {
        return _baseStrategyWrapper;
    }

    void setCommonMethodsWrapper(CommonMethodsWrapper *commonMethodsWrapper)
    {
        _commonMethodsWrapper = commonMethodsWrapper;
    }

    CommonMethodsWrapper* getCommonMethodsWrapper()
    {
        return _commonMethodsWrapper;
    }

    virtual void getDllVersionString(QString &dllVersionString){}
    virtual void setBasePointer(BaseStrategyWrapper *ptr){}
    virtual void initDisplay(){}
    virtual void onFirstLegSymbolFocusOut(){ std::cout << " onFirstLegSymbolFocusOut " << std::endl;}
    virtual void onFirstLegAccountChanged(bool isChecked){std::cout << " onFirstLegSymbolFocusOut " << std::endl;}
    virtual void onAddPushButtonClicked(){ std::cout << " onAddPushButtonClicked " << std::endl;}
    virtual void onNewPushButtonClicked(){}
    virtual void onEditPushButtonClicked(){}
    virtual void onCommitPushButtonClicked(){}
    virtual void onStopAllPushButtonclicked(){}
    virtual void onRemovePushButtonClicked(){}
    virtual void onStopPushButtonClicked(){}
    virtual void onRunPushButtonClicked(){}
    virtual void loadDataFromMarketWatch(qlonglong symbolId,short option){}
    virtual void sendUserResponse(QMessageBox::StandardButton ret,QSharedPointer<API2::Strategy> strategyResponseSharedPtr){}
    virtual bool validateData(API2::PORTFOLIO_STATE state){ return false; }
    virtual bool buildCommandFromUi(API2::PORTFOLIO_STATE state){return true;}
    virtual void updateSymbolIdsDetail(int row,bool isUpdateAll = false){}
    virtual void updateRemainingFeilds(int row,QSqlRecord &adminTokenIdData){}
    virtual bool updateRemainingQty(int row){ return false; }
    virtual void setCommandParameters(QSqlRecord &record,int stgCount,short type){}
    virtual bool setTotalQtyForLegs(int row,short type,QSqlRecord &oldRecord,const QList<BaseSymbolIds *> &symbolIdsList){return true;}
    virtual void populateUIPanels(int row,QSqlRecord &record,bool isNew){}
    virtual void applyUIValidation(short,short state){}
    virtual void updateEditableFieldColor(int row,QColor color){}
    virtual bool updateStrategyDefaultValues(qlonglong adminTokenIdNew){ return false; }
    virtual void clearCustomStructure(qlonglong adminTokenIdNew){}
    virtual bool isTotalQtyVailid(int row){return true;}
    virtual bool isRatioUnChanged(int row) { return true;}
    virtual void onColumnDoubleClicked(QModelIndex index) {}
    virtual void updateDisableColumnsColor(int row){}
    virtual void setColumnCustomColor(int row){}
    virtual bool isSpreadAllowed(short strategy){ return false; }
    virtual short isIvstrategy(short strategy, int row = -1){ return -1; }
    virtual bool isNoRemainingQty(int row){return false;}
    virtual bool isBuySellSpreadDiff(short strategy){ return false; }
    virtual void convertToLots(QSqlRecord &record){}
    virtual void convertToLots(QModelIndex index){}
    virtual void allUIValidation(int row = -1, short strategy=STRATEGY_TYPE_MAX){}
    virtual void setPortfolioDefaultValues(QStringList  &portfolioRow){}
    virtual bool readyStateValidations(int row,QSqlRecord &dbRecord){return true;}
    virtual void spreadCalculationMethod(int row,QList<BaseSymbolIds> &symbolIdsList){}
    virtual void onSpacePressed(){}
    virtual void onAltMPressed(){}

    virtual void onEscapePressed(){}
    virtual void onCtrlSpacePressed(){}
    virtual void onUpKeyPressed(){}
    virtual void OnDownKeyPressed(){}
    virtual void onRunActivated(){}
    virtual void onAltSPressed(){}
    virtual void onAltOPressed(){}
    virtual void setApiCommand(API2::UserParams*,QSqlRecord &record,int stgCount,short type){}
    virtual void setApiCommand(API2::UserParams*,QSqlRecord &record,int stgCount,short type,API2::apiOrderBookParams *ptr){}
    virtual API2::UserParams * getAPICommand(){ return NULL; }
    virtual bool isSpreadCalculationAllowed(){return true;}
    virtual bool isPortfolioNamePresent(){return true;}
    virtual bool isStrategyLegPresent(){return true;}
    virtual bool isSidTotalQtyHandling(){return true;}
    virtual void receiveStrategyResponse(API2::Strategy &strategyResponse){}
    virtual void updateTrades(const RSP::OrderConfirmation &orderConfirmation){}
    virtual UNSIGNED_LONG getTotalQuantityForLegs(API2::LEGS){ return 0; }
    virtual void receiveCustomResponse(API2::API2_CustomResponse &apiCustomResponse){}
    virtual bool showSpreadPopup(){ return false; }
    virtual bool showRemovePopup() { return true;}
    virtual void getHitTrySpread(short spreadType,
                                 const QList<BaseSymbolIds *> &symbolIdsList,
                                 SpreadDetails *spreadDetail,
                                 int row=-1){}
    virtual void updateAccountDetail(const int row){}
    virtual void keyPressEventStrategySpecific(){}
    virtual void populateIvUnderlying(const qlonglong &symbolId,const int &count){}
    virtual bool validatePortFolioData(QStringList  &dataList,QString &errorText,int portfolioCount){return true;}
    virtual void showHideCheckBoxClicked(bool isChecked){}
    virtual void revertEditableFeildData(int row){}
    virtual void firstLegSymbolChanged(){}
    virtual void onFirstLegMarketChanged(){}
    virtual void onFirstLegExpiryChanged(){}
    virtual void onFirstLegOptTypeChanged(){}
    virtual void secondLegSymbolChanged(){}
    virtual void onSecondLegMarketChanged(){}
    virtual void onMarketChanged(){}
    virtual void on_radioButtonClientAccount1_toggled(bool checked){}
    virtual bool terminateValidation(int row,QString &error){return true;}
    virtual bool isAlwaysArchive(){return false;}
    virtual void updateFieldsOnLoadOld(int row){}
    virtual void onRowClickedNotifier(int rowClicked){}
    virtual void onShowHideLegs(){}
    virtual void updateOldStrategyId(qlonglong strategyId,qlonglong adminTokenId){}
    virtual bool byPassRunAddedStrategy(){return false;}
    virtual bool showRunAddedStrategyPopup(){return true;}
    virtual bool isWaitStateSupported(){return false;}
    virtual void rowRemovedNotifier(int row ,int pid=0){}
    virtual bool isSpreadAlgo(){return false;}
    virtual bool showAdditionalSpreadPopups(short strategy, QSqlRecord &adminTokenIdData, bool isModify = false){ return false; }
    virtual void updateAdditionalValuesInPortfolio(QStringList &dataList){}
    virtual bool isDisplayInLotsAllowed(){return false;}
    virtual bool validatePortFolioDataOnLoadOld(qlonglong adminTokenId){return true;}
    virtual bool isSameSidHandling(){return false;}
    virtual void updateCustomDbValuesOnLoadOld(){}
    virtual bool validatePortFolioDataWithErrorText( qlonglong adminTokenId ,
                                                     QStringList &errorText)
    {return true;}

    virtual QKeySequence getStrategyShortCut(short orderMode){ return QKeySequence::UnknownKey; }
    virtual void showByPopulatingSymbolPanel(qlonglong symbolId, QKeySequence sequence=QKeySequence::UnknownKey){}
    virtual bool isStrategyCompletedState(int row){return false;}
    virtual bool isTruncateOnArchive(){return false;}
    virtual QString getSymbolString(bool isAdd,int row = -1){ return ""; }
    virtual void fillOldPositionData(QStringList &dataList){}
    virtual void closeOpenDialog(){}
    virtual void resetTotalQtyForLegs(){}
    virtual void insertCustomSymbolDetailParameters(BaseSymbolIds* symbolIds,int row){}
    virtual QString getTrackerTableName(){return "";}
    virtual bool isTracker() { return false;}
    virtual void loadOldTrackerData(){}
    virtual void firstLegAccountUpdated(){}
    virtual void secondLegAccountUpdated(){}
    virtual QString getStrategyDisplayName(){return "";}
    virtual void thirdLegAccountUpdated(){}
    /**
       * @brief replacePortfolioValuesOnSave replace portfolio values that need to changed while saving portfolio
       * @param QStringList &dataList
       */
    virtual void replacePortfolioValuesOnSave(QStringList &dataList){}
    /**
       * @brief replacePortfolioValuesOnLoad replace portfolio values that need to changed while loading portfolio
       * @param QStringList &dataList
       */
    virtual void replacePortfolioValuesOnLoad(QStringList &dataList){}
    /**
       * @brief modifySaveFileHeader modify save file header in case implementing custom portfolio save
       * @param QString &headerRow
       */
    virtual void modifySaveFileHeader(QString &headerRow){}
    virtual void updateSidQty(qlonglong row){}
    virtual void changesOnTermiantion(int rowClicked){}
    virtual bool isStrategyIdExists(qlonglong strategyId) { return false; }

    virtual bool isUniqueSpreadHandling() { return false; }

    /**
     * @brief  getUniqueSpreadKeyValuePair-> used for unique spread key on addding,loading portfolio, eq. -> uniquekey =  "Symbol1 : Symbol 2 = Spread "
     * @param  QPair<QString, QString > &uniqueSpreadKeyValuePair,int row = -1 , const QStringList &dataList = QStringList()
     * @return void
     */
    virtual void getUniqueSpreadKeyValuePair(QPair<QString, QString > &uniqueSpreadKeyValuePair,int row = -1 , const QStringList &dataList = QStringList()) { }

    virtual bool isPortfolioNewLoadSaveHandling(){ return false; }

    virtual void updateNonPortfolioDbParams(QMap<QString,QString> &nonPortfolioDbParams,QStringList &dataList) { }

    /**
      * @brief destroyDependendObjects destroy objects dependent on basestrategywrapper from its destructor
      */
    virtual void destroyDependendObjects(){}
    virtual void updateCustomValuesInUiOnModify(int row) { }
    virtual bool customUniqueSpreadHandlingCheck(int row = -1 , const QStringList &dataList = QStringList()){ return true; }
    virtual bool isBidAllowed() { return false; }
    virtual bool isIocAllowed() { return false; }
    virtual bool isMulIocAllowed() { return false; }


public slots:
    virtual void onModifyStrategy(){}

};


class CommonMethodsWrapper
{

public:
    virtual QString getNotApplicableStr(){ return ""; }
    virtual QString getTrueStr(){ return ""; }
    virtual QString getStockStr(){ return ""; }
    virtual QString getFutureStr(){ return ""; }
    virtual QString getOptionStr(){ return ""; }
    virtual QString getSpreadStr(){ return ""; }
    virtual QString getProStr(){ return ""; }
    virtual QString getClientStr() {return ""; }
    virtual QString getNormalStr() { return ""; }
    virtual QString getMarket(const UNSIGNED_CHARACTER &exchangeId){ return ""; }
    virtual QString getInstrumentTypeBriefIndex(){ return ""; }

    virtual UNSIGNED_CHARACTER getExchangeId(const QString &market){ return ' '; }

    virtual qlonglong gcd(qlonglong num1,qlonglong num2){ return 1; }

    virtual qlonglong gcd(qlonglong num1,qlonglong num2, qlonglong num3){ return 1; }

    virtual qlonglong gcd(qlonglong num1,qlonglong num2, qlonglong num3, qlonglong num4){ return 1; }



    /**
      *@brief compareRatio
      *@param QList<qlonglong> &firstList
      *@param QList<qlonglong> &secondList
      *@param int limit
      * check is firstList and secondList Ratio is Valid
      */
    virtual bool compareRatio(QList<int> &firstList ,QVector<qlonglong> &secondList,int limit){ return false; }

    virtual bool compareRatio(QVector<qlonglong> &firstList ,QVector<qlonglong> &secondList,int limit) { return false; }

    virtual void removeFocusFromPushButton(QPushButton *button){}

    virtual short getSecurityType(QString securityType){ return -1; }

    virtual QString getTimeFromSec(UNSIGNED_LONG secSinceEpoch){ return ""; }

    virtual QString getOrderTypeStr(short orderType){ return ""; }

    virtual void setItem(QStandardItemModel *tableModel, int row, int col,  QVariant data, Qt::AlignmentFlag  alignmentFlag = Qt::AlignCenter) {}

    virtual QString getOrderValidityStr(unsigned short orderValidity){ return ""; }

    virtual short getOrderValidity(QString orderValidity) { return -1; }


    virtual QStandardItem * getItem(QVariant data,Qt::AlignmentFlag  alignmentFlag = Qt::AlignCenter){ return NULL; }


    virtual QStandardItem * getItem(QVariant data, QBrush& brush, Qt::AlignmentFlag  alignmentFlag){ return NULL; }


    virtual short getGenericBaseType(QString baseType){ return -1; }

    virtual QString getGenericBaseTypeStr(short baseType){ return ""; }

    virtual short getGenericStrategyType(QString threeLegStrategy,short leg){ return -1; }

    virtual QString getGenericStrategyTypeStr(short threeLegStrategy){ return ""; }

    virtual QString getSpreadTypeStr(short twoLegThreeLegSpreadType){ return ""; }

    virtual QString getDiffTypeStr( short diffType ){ return ""; }

    virtual QString getLegTypeStr(short leg){ return ""; }

    virtual short getLegType(QString str){ return -1; }

    virtual short getExecutionVolumn(QString type){ return -1; }

    virtual QString getExecutionVolumnStr(short type){ return ""; }

    virtual QString getStrategyExecTypeStr(short strategyExecType){ return ""; }

    virtual short getStrategyExecType(QString strategyExecType){ return -1; }

    virtual  QString getInstrumentTypeString(short securityType){ return ""; }


    virtual QString getInstrumentTypeStr(QString instrument){ return ""; }


    virtual QString getInstrumentTypeStr(short securityType){ return ""; }


    virtual QString getInstrumentStr(short securityType){ return ""; }

    virtual QString getInstrumentTypeFromName(QString instrument){ return ""; }

    virtual QString getTwoLegArbitHedgeMethod(short hedgeMethod){ return ""; }


    virtual short getTwoLegArbitHedgeMethod(QString hedgeMethod){ return -1; }

    virtual QString getOrderMode(short orderMode ){ return ""; }

    virtual  short getOrderMode(QString orderMode){ return -1; }


    virtual  QString getTwoLegThreeLegSpreadTypeStr(short twoLegThreeLegSpreadType){ return ""; }

    virtual short getTwoLegThreeLegSpreadType(QString strSpreadType){ return -1; }


    virtual QString getStrategyState(short responseType){ return ""; }


    virtual short getGenericExecutionStyle(QString baseType){ return -1; }


    virtual QString getGenericExecutionStyleStr(short baseType){ return ""; }

    virtual QString getOptionModeStr(short optMode){ return ""; }


    virtual QString getOptionModeStr(QString optMode){ return ""; }

    virtual  short getOptionMode(QString optionType){ return -1; }

    virtual QString getOptionType(QString optionTypeStr){ return ""; }

    /**
     * @brief  getCommonMethodsWrapper()->getContinuousHedgeMode
     * @param  QString mode
     * @return CMD::CONT_HEDGING_MODE EnumMapping
     */
    virtual short getContinuousHedgeMode(QString mode){ return -1; }
    /**
     * @brief  getCommonMethodsWrapper()->getContinuousHedgeModeStr
     * @param  CMD::CONT_HEDGING_MODE mode
     * @return QString
     */
    virtual QString getContinuousHedgeModeStr(short mode){ return ""; }

    virtual void updateTableView(QTableView *tableview){}
    virtual QString getStrategyVersion(){return "";}
    virtual int getCurrentExpiryIndexSpread(QComboBox *comboBoxExpiry) {return 0;}
    virtual void showMessage(QWidget *parent, QString title, QString message){}
    virtual bool isClientCodePresent(const QString &market, const QString &inst){return false;}
    virtual qlonglong getClosePrice(qlonglong symbolId){return 0;}
    virtual QString maturityDayMonYearToDate(int day, int yearMon,const QString &format = QString("dd MMM yyyy")){return Unknownstr;}

    virtual qlonglong getCurrentMonthFutureSymbolId(const QString& source, const QString& market, const QString& symbol){return 0;}
    virtual bool eventFilterStrikePriceCombobox(QObject *object, QEvent *event, QHash<QObject *, QString> &hashComboSearchedString, qlonglong &keyPressEventTimer){return false;}
    virtual short getSegmentFromInstrument(const QString& instrument){return -1;}
    virtual bool isQuoteAvailable(qlonglong symbolId){ return false; }
    virtual int getSpreadTimer(){return 0;}
    virtual int getQuoteWaitCounter(){return 0;}
    virtual short getExpiryInclusionExclusion(){return -1;}
    virtual void getTrades(qlonglong symbolId, qlonglong strategyId, qlonglong &filledBuyQty,
                              float &filledBuyPrice, qlonglong &filledSellQty, float &filledSellPrice,
                               QString &buyPriceStr, QString &sellPriceStr) {}



    // Filter Handling
    virtual QSortFilterProxyModel* getSortFilterProxyModel(QList<short> &filterColList, QObject* parent=0){ return NULL; }
    virtual QHeaderView* getFilterHeaderView(QVector<short> &filterTypeList, QTableView* tableView){ return NULL; }
    virtual QWidget *getFilterHeaderViewWidget(QHeaderView *headerView, short filterWidget){return NULL;}
    virtual void onTextFilterChanged(QSortFilterProxyModel *proxyModel, QHeaderView *headerView, QList<short> &filterColList){}
    virtual void setFilterActive(QSortFilterProxyModel *proxyModel,bool isFilterActive){}
    virtual void setFilterVisible(QHeaderView *headerView,bool isFilterActive){}

    virtual void convertBPSToSpread(qlonglong &spread,short orderMode ,qlonglong price,qlonglong dividend = 0){}
    virtual qlonglong getOppositePrice(qlonglong symbolId , short orderMode){ return 0; }
    virtual qlonglong getSymbolIdFromISIN(const QString &ISIN, short exchangeId){ return 0; }
    virtual void convertToMultipleOfTickSize(qlonglong &hitSpread,qlonglong symbolId){}
    virtual void getCurrentMonthExpiry(QComboBox * comboBox){}
    virtual void getNextMonthExpiry(QComboBox * comboBox){}
    virtual bool checkForBannedScrips(qlonglong symbolId){ return false; }
    virtual void getExpiryList(const QString& symbol,const QString& market ,QStringList &expiryList ){}
    virtual void getClientInfoFromConfirmation(const RSP::OrderConfirmation &confirmation, QString &parentClCode, QString &childClCode, QString& partCode){}
    virtual void getPriceAccordingToTicksize(qlonglong &price , int ticksize, short orderMode){}
    virtual void setInstrTypeFromMkt(QComboBox * comboBox, QString market) {}
    virtual void printSqlError(QSqlQuery &query){}
    virtual const API2::SymbolDetail& getSymbolIdDetail(qlonglong symbolId){ return API2::SymbolDetail(); }
    virtual void  getPrecisionAndMultiplier(qlonglong symbolId, double &multiplier, short &precision){}
    virtual short configFileValue(const char *str){ return -1; }
    virtual void getIvVegaPrice(qlonglong symbolId,
                         qlonglong price,
                         short,
                         qlonglong underlyingSymbolId,
                         qlonglong &ivPrice,
                         double &vega,
                         bool isVegaCalculate){}
    virtual void insertTradeWiseTrackerList(QSharedPointer< API2::TradeWiseTrackerData> &tradeWiseTrackerData){}

    virtual bool isUHedgeEnable()
    {
        return false;
    }
    ////

};
#endif // BASESTRATEGYWRAPPER_H
