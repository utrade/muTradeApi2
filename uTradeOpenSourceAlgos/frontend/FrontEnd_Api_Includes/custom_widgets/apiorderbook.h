#ifndef APIORDERBOOK_H
#define APIORDERBOOK_H

#if IS_QT4_VERSION
#include <QDialog>
#else
#include <QtWidgets/QDialog>
#endif
#include "../dll_includes/baseStrategyWrapper.h"
#include "../dll_includes/sharedStrutures.h"

namespace Ui {
class apiOrderBook;
}

class apiOrderBook : public QDialog
{
    Q_OBJECT
    
public:
    explicit apiOrderBook(APIWrapper *ptr,QWidget *parent = NULL, bool isQtyEnabled=false);
    ~apiOrderBook();
    void insertNewRowInOrderBook(RSP::OrderConfirmation& orderConfirmation);
    void enableParams(bool isEnable = false);

    enum colOrderBook
    {
        colOrderBook_OrderId,
        colOrderBook_ExOrderId,
        colOrderBook_OrigOrderId,
        colOrderBook_Mode,
        colOrderBook_SymbolId,
        colOrderBook_Symbol,
        colOrderBook_OrderStatus,
        colOrderBook_Quantity,
        colOrderBook_Price,
        colOrderBook_strategyId,
        colOrderBook_TotalFillQty,
        colOrderBook_ParentClCode,
        colOrderBook_ChildClCode,
        colOrderBook_PartCode
    };

    enum ModificationIndex
    {
        ModificationIndex_NORMAL=0,
        ModificationIndex_ORDER_CANCEL=1,
        ModificationIndex_ORDER_MODIFY=2,
        ModificationIndex_MAX
    };


public slots:
    void onCurrentRowChanged(QModelIndex newIndex,QModelIndex oldIndex);

    void on_pushButtonEdit_clicked();

    void on_pushButtonModify_clicked();
    void receiveDataFromSgOrderBook();

    void on_pushButtonCancel_clicked();
    void onTextFilterChanged();
    void onAddRemoveFilter();
    void on_apiOrderBookTableView_customContextMenuRequested(const QPoint &pos);

private:
    Ui::apiOrderBook *ui;
    QStandardItemModel *_apiOrderBookModel;
    QMenu *_contextMenu;
    QAction *_actionResizeToContents;
    QAction *_actionHideShowColumns;
    QStringList _columnList;
    QVector<qlonglong> _vectorOrderId;
    QTimer _orderBookTimer;

    APIWrapper *_ApiPointer;
    API2::apiOrderBookParams *apiBookParams;
    //filter handling
    QShortcut *_shortCutFilter;
    QList<short> _filterColList;
    QSortFilterProxyModel *_proxyModel;
    QHeaderView* _headerView;
    void setFilterHeader();
    bool _isFilterActive;
    bool isQtyWidEnabled;
    ////
    void initializeColumnList();
    void signalSlots();
    void initializeModel();
    void initialize();
    void updateModel(int row,RSP::OrderConfirmation& orderConfirmation);
    void populateUi();
    void hideShowColumns();
    bool isEnableState();
    void setMoveProperty();
};

#endif // APIORDERBOOK_H
