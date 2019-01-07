#ifndef Icebergui_H
#define Icebergui_H

#include "icebergparams.h"
#include <qglobal.h>
#include "../../FrontEnd_Api_Includes/dll_includes/baseStrategyWrapper.h"
#include <QDialog>
#include "../../FrontEnd_Api_Includes/dll_includes/StrategyConstants.h"
#include "../../api2/api_includes/api2UserCommands.h"

namespace Ui {
class Icebergui;
}

class Icebergui : public APIWrapper
{
    Q_OBJECT

public:
    enum order_Mode
    {
        order_Mode_BUY,
        order_Mode_SELL,
        order_Mode_MAX
    };

    enum order_Type
    {
        order_Type_LIMIT,
        order_Type_MARKET,
        order_Type_MAX
    };

    enum fill_Type
    {
        fill_Type_DAY,
        fill_Type_IOC,
        fill_Type_MAX
    };

    static Icebergui& getInstance(QWidget *parent = 0)
    {
        if ( _Icebergui == 0 )
        {
            _Icebergui = new Icebergui(parent);
        }
        return *_Icebergui;
    }

    explicit Icebergui(QWidget *parent = 0);
    ~Icebergui();

private:
    Ui::Icebergui *ui;
    static Icebergui *_Icebergui;
    icebergparams *_iceBergParams;
    QStandardItemModel *_baseTableModel;
    API2::StrategyParamMap *_paramsMap;
    QHash<qlonglong,qlonglong > _pidSidQty;
    QHash<int,int> _hashStrategyIdPortfolioId;
    qlonglong quantity;
    long long _time;
    bool _isNewStrategyWriteMethod;
    QTimer _timer;
    void initialize();
    void populateElements();
    void setDefaultIndex();
    void setSymbolPanel();
    void populateOrderTypes();
    void setFilters();
    void populateFillTypes();
    void populateFillType(QComboBox * combofill);
    void setConnections();
    inline void displayWarningMessage(const QString &message);
    void enableDisableAccountDetails();
    qlonglong getEpochTime(QTime time);
    void getDllVersionString(QString &dllVersionString);
    void setExpiryDate();
    bool isSpreadAlgo();
    qlonglong getCurrentStrategyId();
    bool validatePortFolioDataOnLoadOld(qlonglong adminTokenId);
    short getOrderType(const QString &orderType);
    bool isOrdertypeValid(const int &orderType);
    int getPortfolioId(int strategyId);
    void setPrecisionDecimal(qlonglong symbolId);
    void applyUIValidation(short transactionType, short state);
    void allUIValidation(int row, short strategy);
    void updateAccountDetail(const int row);
    void updateTradedQty(int row );
    long long getTotalTradedQuantity(long long pid);
    bool isStrategyLegPresent();
    void initDisplay();
    bool validateData(API2::PORTFOLIO_STATE state);
    void updateSymbolIdsDetail(int row, bool isUpdateAll);
    bool buildCommandFromUi(API2::PORTFOLIO_STATE state);
    bool showSpreadPopup();
    bool isSpreadCalculationAllowed();
    bool setTotalQtyForLegs(int row,short transactiontype,
                            QSqlRecord &oldRecord,
                            const QList<BaseSymbolIds*> &symbolIdsList);
    bool updateRemainingQty(int row);
    bool isPortfolioNamePresent();
    bool isSidTotalQtyHandling();
    void updateRemainingFeilds(int row, QSqlRecord &adminTokenIdData);
    void setApiCommand(API2::UserParams *apiParams,
                       QSqlRecord &record,
                       int stgCount,
                       short type);
    void populateUIPanels(int row, QSqlRecord &record, bool isNew);
    void updateTrades(const RSP::OrderConfirmation &orderConfirmation);
    void updateEditableFieldColor(int row, QColor color);
    void setBasePointer(BaseStrategyWrapper *ptr)
    {
        setBaseWrapper(ptr);
    }
    void initializeTabOrder();
    void updateSidQty(qlonglong row);
    void receiveCustomResponse(API2::API2_CustomResponse &apiCustomResponse);
    bool updateStrategyDefaultValues(qlonglong adminTokenIdNew);
    void rowRemovedNotifier(int row,int pid);
    void keyPressEvent(QKeyEvent * event);
    bool validatePortFolioData(QStringList &dataList,
                               QString &errorText,
                               int portfolioCount);
    bool calculateRefrencePrice(const QString &segmentType,
                                const QString &spreadType,
                                const QString& refPrice,
                                short orderMode,
                                bool fromFileFlag = false);
    short getOrderMode(const QString & orderMode);
    QString getStrategyDisplayName();
    long long getTradedQuantity(qlonglong adminTokenId);
    void updateTradesinDb(qlonglong adminTokenId,int filledQuantity);
    void replacePortfolioValuesOnSave(QStringList &dataList);
    void replacePortfolioValuesOnLoad(QStringList &dataList);
    bool isNewState();
    bool isPortfolioNewLoadSaveHandling();
    bool isTotalQtyVailid(int row);
    bool isTotalQtyValidOnNew(int row);

private slots:
    void updateDataOnTimer();
    void onOrderTypeChanged();
    void onCtrlSpacePressed();
    void onEscapePressed();
    void onUpKeyPressed();
    void OnDownKeyPressed();
    void onClosePushButtonClicked();
    void onAltMPressed();
    void on_editLotSize_textChanged(const QString &arg1);
    void onStopPushButtonClicked();
    void onAddPushButtonClicked();
    void onNewPushButtonClicked();
    void onEditPushButtonClicked();
    void onCommitPushButtonClicked();
    void onRemovePushButtonClicked();
    void onStopAllPushButtonclicked();
    void onRunPushButtonClicked();
    void onAltSPressed();
    void onAltOPressed();
    void receiveStrategyResponse(API2::Strategy &strategyResponse);
    void onRemoveAllClicked();
};

#endif // Icebergui_H
