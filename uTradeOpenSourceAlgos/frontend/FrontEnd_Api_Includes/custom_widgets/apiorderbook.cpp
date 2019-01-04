#include "apiorderbook.h"
#include "ui_apiorderbook.h"

apiOrderBook::apiOrderBook(APIWrapper *ptr, QWidget *parent, bool isQtyEnabled) :
    QDialog(parent),
    _apiOrderBookModel(new QStandardItemModel(this)),
    _contextMenu(new QMenu(this)),
    ui(new Ui::apiOrderBook),
    _isFilterActive(false),
    _ApiPointer(ptr),
    isQtyWidEnabled(isQtyEnabled),
    apiBookParams(new API2::apiOrderBookParams())
{
    ui->setupUi(this);
    initialize();
}


void apiOrderBook::initialize()
{
    setMoveProperty();
    setMinimumSize(width(), height());
    ui->doubleSpinBoxPrice->setMinimum(-999999999.000000);
    initializeColumnList();
    ui->pushButtonModify->setEnabled(false);
    ui->spinBoxQty->setVisible(isQtyWidEnabled);
    ui->labelQty->setVisible(isQtyWidEnabled);
    _actionResizeToContents = _contextMenu->addAction("Resize To Contents");
    _actionHideShowColumns = _contextMenu->addAction("Hide/Show Columns");
    ui->apiOrderBookTableView->setWordWrap(false);
    setWindowTitle(_ApiPointer->getBaseWrapper()->getstrategyName()+ " OrderBook ");
    setWindowFlags( windowFlags() | Qt::WindowMinimizeButtonHint);
    initializeModel();
    signalSlots();
}

void apiOrderBook::signalSlots()
{
    connect(ui->apiOrderBookTableView->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(onCurrentRowChanged(QModelIndex,QModelIndex)));
    connect(&_orderBookTimer,SIGNAL(timeout()), this, SLOT(receiveDataFromSgOrderBook()));
    _orderBookTimer.start(500);
}

void apiOrderBook::receiveDataFromSgOrderBook()
{
    QHash<QString, RSP::OrderConfirmation*>  confirmationMap;
    _ApiPointer->getBaseWrapper()->getOfflineConfirmationMap(confirmationMap);
    QHash<QString, RSP::OrderConfirmation*>::iterator it;

    if(_apiOrderBookModel->rowCount() == 0 )
        ui->doubleSpinBoxPrice->setValue(0);
    if(confirmationMap.isEmpty())
    {
        _apiOrderBookModel->setRowCount(0);
    }
    else
    {
        int eventCounter = 0;
        for(int row=_apiOrderBookModel->rowCount()-1;row>=0;row--)
        {
            QString key =  _apiOrderBookModel->item(row, colOrderBook_ExOrderId)->data(Qt::DisplayRole).toString();
            RSP::OrderConfirmation *confirmation = 0;
            it = confirmationMap.find(key);
            if(it != confirmationMap.end()  && _ApiPointer->isStrategyIdExists(it.value()->getStrategyId()))
            {
                confirmation = it.value();
                if( confirmation != NULL )
                {
                    updateModel(row, *confirmation);
                    delete confirmation;
                    confirmation = 0;
                }
                confirmationMap.erase(it);
            }
            else
                _apiOrderBookModel->removeRow(row);
            eventCounter++;
            if(eventCounter == 100)
            {
                eventCounter = 0;
                qApp->processEvents();
            }
        }
        it = confirmationMap.begin();
        while(it != confirmationMap.end())
        {
            RSP::OrderConfirmation *confirmation = it.value();
            if(confirmation != NULL)
            {
                insertNewRowInOrderBook(*confirmation);
                delete confirmation;
                confirmation = 0;
            }
            eventCounter++;
            if(eventCounter == 100)
            {
                eventCounter = 0;
                qApp->processEvents();
            }
            it = confirmationMap.erase(it);
        }
    }
    _proxyModel->invalidate();
    _ApiPointer->getCommonMethodsWrapper()->updateTableView(ui->apiOrderBookTableView);
}

void apiOrderBook::insertNewRowInOrderBook(RSP::OrderConfirmation &orderConfirmation)
{
    if(!_ApiPointer->isStrategyIdExists(orderConfirmation.getStrategyId()))
        return;
    _apiOrderBookModel->blockSignals(true);
    QList<QStandardItem *> ItemLists;
    QBrush brush((API2::DllCMD::OrderMode_BUY == orderConfirmation.getOrderMode()) ? QColor("blue") : QColor("red"));
    ItemLists.append(_ApiPointer->getCommonMethodsWrapper()->getItem(orderConfirmation.getClOrderId(), brush, Qt::AlignRight));
    ItemLists.append(_ApiPointer->getCommonMethodsWrapper()->getItem(QString::fromStdString(orderConfirmation.getExchangeOrderId()), brush, Qt::AlignRight));
    ItemLists.append(_ApiPointer->getCommonMethodsWrapper()->getItem("0", brush, Qt::AlignRight));// OrigoOrderId
    ItemLists.append(_ApiPointer->getCommonMethodsWrapper()->getItem(_ApiPointer->getCommonMethodsWrapper()->getOrderMode((API2::DllCMD::OrderMode)orderConfirmation.getOrderMode()), brush, Qt::AlignLeft));
    const  API2::SymbolDetail& sd = _ApiPointer->getBaseWrapper()->getSymbolIdDetail(orderConfirmation.getSymbolId());

    qlonglong totalFillQty = orderConfirmation.getTotalFillQuantity();
    qlonglong pendingQty = (orderConfirmation.getOrderQuantity()) - totalFillQty;
    QString orderStatus = (pendingQty) != orderConfirmation.getOrderQuantity() ? _ApiPointer->getBaseWrapper()->getOrderStatus(API2::CONSTANTS::RSP_OrderStatus_PARTIALLY_FILLED) : _ApiPointer->getBaseWrapper()->getOrderStatus(orderConfirmation.getOrderStatus());

    ItemLists.append(_ApiPointer->getCommonMethodsWrapper()->getItem(QString::number(orderConfirmation.getSymbolId()), brush, Qt::AlignLeft));
    ItemLists.append(_ApiPointer->getCommonMethodsWrapper()->getItem(sd.scripName, brush, Qt::AlignLeft));

    ItemLists.append(_ApiPointer->getCommonMethodsWrapper()->getItem(orderStatus, brush, Qt::AlignLeft));
    ItemLists.append(_ApiPointer->getCommonMethodsWrapper()->getItem(orderConfirmation.getOrderQuantity(), brush, Qt::AlignRight));
    ItemLists.append(_ApiPointer->getCommonMethodsWrapper()->getItem(QString::number((double)(orderConfirmation.getOrderPrice())/sd.multiplier, 'f', sd.precision), brush, Qt::AlignRight));
    ItemLists.append(_ApiPointer->getCommonMethodsWrapper()->getItem(orderConfirmation.getStrategyId(), brush, Qt::AlignRight));
    ItemLists.append(_ApiPointer->getCommonMethodsWrapper()->getItem(orderConfirmation.getTotalFillQuantity(), brush, Qt::AlignRight));
    QString parentClCode,childClCode,partCode;
    _ApiPointer->getCommonMethodsWrapper()->getClientInfoFromConfirmation(orderConfirmation,parentClCode,childClCode,partCode);
    ItemLists.append(_ApiPointer->getCommonMethodsWrapper()->getItem(parentClCode, brush, Qt::AlignRight));
    ItemLists.append(_ApiPointer->getCommonMethodsWrapper()->getItem(childClCode, brush, Qt::AlignRight));
    ItemLists.append(_ApiPointer->getCommonMethodsWrapper()->getItem(partCode, brush, Qt::AlignRight));

    _apiOrderBookModel->appendRow(ItemLists);
    _apiOrderBookModel->blockSignals(false);
}

void apiOrderBook::onCurrentRowChanged(QModelIndex newIndex, QModelIndex oldIndex)
{
    if(!newIndex.isValid())
        return;
    int row = _proxyModel->mapToSource(ui->apiOrderBookTableView->currentIndex()).row();
    const  API2::SymbolDetail &sd = _ApiPointer->getBaseWrapper()->getSymbolIdDetail(_apiOrderBookModel->item(row,colOrderBook_SymbolId)->data(Qt::DisplayRole).toLongLong());
    ui->spinBoxQty->setValue(  _apiOrderBookModel->item(row,colOrderBook_Quantity)->data(Qt::DisplayRole).toLongLong());
    ui->spinBoxQty->setSingleStep(sd.lotSize);
    ui->doubleSpinBoxPrice->setValue(  _apiOrderBookModel->item(row,colOrderBook_Price)->data(Qt::DisplayRole).toDouble());
    ui->doubleSpinBoxPrice->setDecimals(sd.precision);
    float singleStep = (float(sd.tickSize )/ pow(10.0,sd.precision));
    ui->doubleSpinBoxPrice->setSingleStep(singleStep);
    enableParams(false);
}

void apiOrderBook::initializeColumnList()
{
    _columnList<<"Order Id"
              <<"Ex Order Id"
             <<"Orig Ord Id"
            <<"Mode"
           <<"Symbol Id"
          <<"Symbol"
         <<"Order Status"
        <<"Quantity"
       <<"Price"
      <<"Strategy Id"
     <<"Total Fill Qty"
    <<"Parent Client Code"
   <<"Child Client Code"
  <<"Part Code";
}

void apiOrderBook::initializeModel()
{
    _shortCutFilter = new QShortcut(Qt::ALT + Qt::Key_F,this,SLOT(onAddRemoveFilter()),0,Qt::WidgetWithChildrenShortcut);
    _apiOrderBookModel->setHorizontalHeaderLabels(_columnList);
    _apiOrderBookModel->setColumnCount(_columnList.size());
    _filterColList << colOrderBook_OrderId << colOrderBook_ExOrderId << colOrderBook_OrigOrderId << colOrderBook_Mode
                   << colOrderBook_SymbolId << colOrderBook_Symbol << colOrderBook_OrderStatus
                   << colOrderBook_Quantity << colOrderBook_Price << colOrderBook_strategyId
                   << colOrderBook_TotalFillQty << colOrderBook_ParentClCode << colOrderBook_ChildClCode
                   << colOrderBook_PartCode;
    _proxyModel = _ApiPointer->getCommonMethodsWrapper()->getSortFilterProxyModel(_filterColList,this);
    _proxyModel->setSourceModel(_apiOrderBookModel);
    ui->apiOrderBookTableView->setModel(_proxyModel);
    setFilterHeader();
    ui->apiOrderBookTableView->setHorizontalHeader(_headerView);

    _ApiPointer->getCommonMethodsWrapper()->setFilterVisible(_headerView,_isFilterActive);
    _ApiPointer->getCommonMethodsWrapper()->setFilterActive(_proxyModel,_isFilterActive);
}

void apiOrderBook::setFilterHeader()
{
    QVector<short> vectorFilterType;
    for(int apiOrderBookModelCounter=0 ; apiOrderBookModelCounter < _apiOrderBookModel->columnCount() ; ++apiOrderBookModelCounter)
        vectorFilterType.push_back(API2::WidgetType_LINEEDIT);

    _headerView = _ApiPointer->getCommonMethodsWrapper()->getFilterHeaderView(vectorFilterType,ui->apiOrderBookTableView);
    for(int apiOrderBookModelCounter=0 ; apiOrderBookModelCounter < _apiOrderBookModel->columnCount(); apiOrderBookModelCounter++)
        connect(_ApiPointer->getCommonMethodsWrapper()->getFilterHeaderViewWidget(_headerView,apiOrderBookModelCounter), SIGNAL(textChanged(QString)), this, SLOT(onTextFilterChanged()));
}

void apiOrderBook::onTextFilterChanged()
{
    _ApiPointer->getCommonMethodsWrapper()->onTextFilterChanged(_proxyModel, _headerView, _filterColList);
    _proxyModel->invalidate();
}

void apiOrderBook::onAddRemoveFilter()
{
    _isFilterActive = !_isFilterActive;

    _ApiPointer->getCommonMethodsWrapper()->setFilterVisible(_headerView,_isFilterActive);
    _ApiPointer->getCommonMethodsWrapper()->setFilterActive(_proxyModel,_isFilterActive);
    onTextFilterChanged();
}

void apiOrderBook::updateModel(int row, RSP::OrderConfirmation &orderConfirmation)
{
    const  API2::SymbolDetail &sd = _ApiPointer->getBaseWrapper()->getSymbolIdDetail((UNSIGNED_LONG)orderConfirmation.getSymbolId());
    int lotSize = 1;
    qlonglong totalFillQty = orderConfirmation.getTotalFillQuantity();
    qlonglong pendingQty = (orderConfirmation.getOrderQuantity()/lotSize) - totalFillQty/lotSize;
    QString orderStatus = (pendingQty*lotSize) != orderConfirmation.getOrderQuantity() ? _ApiPointer->getBaseWrapper()->getOrderStatus(API2::CONSTANTS::RSP_OrderStatus_PARTIALLY_FILLED) : _ApiPointer->getBaseWrapper()->getOrderStatus(orderConfirmation.getOrderStatus());
    _apiOrderBookModel->blockSignals(true);
    _apiOrderBookModel->item(row,colOrderBook_OrderId)->setData(QString::number((UNSIGNED_LONG)orderConfirmation.getClOrderId()),Qt::DisplayRole);
    _apiOrderBookModel->item(row,colOrderBook_ExOrderId)->setData(QString::fromStdString(orderConfirmation.getExchangeOrderId()),Qt::DisplayRole);
    _apiOrderBookModel->item(row,colOrderBook_OrigOrderId)->setData(QString::number((UNSIGNED_LONG)orderConfirmation.getOriginalClOrderId()),Qt::DisplayRole);
    _apiOrderBookModel->item(row,colOrderBook_Mode)->setData(_ApiPointer->getCommonMethodsWrapper()->getOrderMode((API2::DllCMD::OrderMode)orderConfirmation.getOrderMode()),Qt::DisplayRole);
    _apiOrderBookModel->item(row,colOrderBook_SymbolId)->setData(QString::number((UNSIGNED_LONG)orderConfirmation.getSymbolId()),Qt::DisplayRole);
    _apiOrderBookModel->item(row,colOrderBook_Symbol)->setData(sd.scripName,Qt::DisplayRole);
    _apiOrderBookModel->item(row,colOrderBook_OrderStatus)->setData(orderStatus,Qt::DisplayRole);
    _apiOrderBookModel->item(row,colOrderBook_Quantity)->setData(QString::number((UNSIGNED_LONG)orderConfirmation.getOrderQuantity()),Qt::DisplayRole);
    _apiOrderBookModel->item(row,colOrderBook_Price)->setData(QString::number((double)(orderConfirmation.getOrderPrice())/sd.multiplier, 'f', sd.precision),Qt::DisplayRole);
    _apiOrderBookModel->item(row,colOrderBook_strategyId)->setData(QString::number((UNSIGNED_LONG)orderConfirmation.getStrategyId()),Qt::DisplayRole);
    _apiOrderBookModel->item(row,colOrderBook_TotalFillQty)->setData(QString::number(totalFillQty),Qt::DisplayRole);
    QString parentClCode,childClCode,partCode;
    _ApiPointer->getCommonMethodsWrapper()->getClientInfoFromConfirmation(orderConfirmation,parentClCode,childClCode,partCode);
    _apiOrderBookModel->item(row,colOrderBook_ParentClCode)->setData(parentClCode,Qt::DisplayRole);
    _apiOrderBookModel->item(row,colOrderBook_ChildClCode)->setData(childClCode,Qt::DisplayRole);
    _apiOrderBookModel->item(row,colOrderBook_PartCode)->setData(partCode,Qt::DisplayRole);
    _apiOrderBookModel->blockSignals(false);
    const QModelIndex &index = _proxyModel->mapToSource(ui->apiOrderBookTableView->currentIndex());
    if(!isEnableState())
    {
        if(index.isValid())
        {
            int row = index.row();
            if(row != -1)
            {
                ui->spinBoxQty->setValue(_apiOrderBookModel->item(row,colOrderBook_Quantity)->data(Qt::DisplayRole).toLongLong());
                ui->doubleSpinBoxPrice->setValue(_apiOrderBookModel->item(row,colOrderBook_Price)->data(Qt::DisplayRole).toDouble());
            }
        }
    }
}

void apiOrderBook::on_apiOrderBookTableView_customContextMenuRequested(const QPoint &pos)
{
    QAction *selectedAction = _contextMenu->exec(ui->apiOrderBookTableView->viewport()->mapToGlobal(pos));
    if(selectedAction == _actionResizeToContents)
        ui->apiOrderBookTableView->resizeColumnsToContents();

    if(selectedAction == _actionHideShowColumns)
        hideShowColumns();
}

void apiOrderBook::hideShowColumns()
{
    QList<int> _alwaysHidden;
    _ApiPointer->getBaseWrapper()->hideShowColumns(ui->apiOrderBookTableView,"ApiOrderBook",_alwaysHidden, this ,true, _apiOrderBookModel);
}

void apiOrderBook::on_pushButtonEdit_clicked()
{
    enableParams(true);
}

void apiOrderBook::enableParams(bool isEnable)
{
    ui->spinBoxQty->setEnabled(isEnable);
    ui->doubleSpinBoxPrice->setEnabled(isEnable);
    ui->pushButtonEdit->setEnabled(!isEnable);
    ui->pushButtonModify->setEnabled(isEnable);
}

void apiOrderBook::on_pushButtonModify_clicked()
{
    QModelIndexList indexList = ui->apiOrderBookTableView->selectionModel()->selectedRows();
    if(!(indexList.size()))
    {
        QMessageBox::warning(this,_ApiPointer->getBaseWrapper()->getFileName(),"No row selected");
        return;
    }
    QString orderIds;
    qlonglong strategyId = 0;
    int lotSize = 0;
    qlonglong totalFillQty = 0;
    QModelIndex index;
    bool isSingleRowSelected = indexList.size() == 1 ;
    qlonglong resetQty = 0;
    QString resetPrice;
    qlonglong symbolId = 0;
    foreach (QModelIndex proxyIndex, indexList)
    {
        index = _proxyModel->mapToSource(proxyIndex);
        if(!index.isValid())
            continue;
        orderIds += _apiOrderBookModel->item(index.row(),colOrderBook_OrderId)->text() + ":";
        if(!strategyId)
            strategyId = _apiOrderBookModel->item(index.row(),colOrderBook_strategyId)->data(Qt::DisplayRole).toLongLong();
        else if(strategyId != _apiOrderBookModel->item(index.row(),colOrderBook_strategyId)->data(Qt::DisplayRole).toLongLong())
        {
            QMessageBox::warning(this,_ApiPointer->getBaseWrapper()->getFileName(),"Cannot modify orders of different strategies");
            return;
        }
        if(!lotSize)
            lotSize = _ApiPointer->getBaseWrapper()->getSymbolIdDetail(_apiOrderBookModel->item(index.row(),colOrderBook_SymbolId)->data(Qt::DisplayRole).toLongLong()).lotSize;

        totalFillQty = _apiOrderBookModel->item(index.row(),colOrderBook_TotalFillQty)->data(Qt::DisplayRole).toLongLong();

        if(isSingleRowSelected)
        {
            resetQty = _apiOrderBookModel->item(index.row(),colOrderBook_Quantity)->data(Qt::DisplayRole).toLongLong();
            resetPrice = _apiOrderBookModel->item(index.row(),colOrderBook_Price)->text();
        }
        if(isQtyWidEnabled && ui->spinBoxQty->value() <= totalFillQty)
        {
            QMessageBox::warning(this,_ApiPointer->getBaseWrapper()->getFileName(),"Qty must be greater than total filled Qty");
            if(isSingleRowSelected)
                ui->spinBoxQty->setValue(resetQty);
            return;
        }
        if(!symbolId)
            symbolId = _apiOrderBookModel->item(index.row(),colOrderBook_SymbolId)->data(Qt::DisplayRole).toLongLong();
    }

    const API2::SymbolDetail &sd = _ApiPointer->getBaseWrapper()->getSymbolIdDetail(symbolId);

    orderIds.chop(1);
    apiBookParams->orderPrice = ui->doubleSpinBoxPrice->text().remove('.').toLongLong();

    if(isQtyWidEnabled)
    {
        if(ui->spinBoxQty->value() > 0 && lotSize && ui->spinBoxQty->value()%lotSize == 0)
            apiBookParams->orderQty = ui->spinBoxQty->value();
        else
        {
            QMessageBox::warning(this,_ApiPointer->getBaseWrapper()->getFileName(),"Quantity should be greater than 0 & multiple of Lot Size");
            if(isSingleRowSelected)
                ui->spinBoxQty->setValue(resetQty);
            return;
        }
    }
    qlonglong price = QString::number(ui->doubleSpinBoxPrice->value(),'f',ui->doubleSpinBoxPrice->decimals()).remove(".").toLongLong();
    if(!(sd.tickSize && (price % sd.tickSize == 0)))
    {
        QMessageBox::warning(this,_ApiPointer->getBaseWrapper()->getFileName(),trUtf8("Price must be multiple of ticksize"));
        if(isSingleRowSelected)
            ui->doubleSpinBoxPrice->setValue(resetPrice.toDouble());
        return ;
    }

    if( (_ApiPointer->getCommonMethodsWrapper()->getSecurityType(sd.contractType) != API2::CONSTANTS::CMD_SecurityType_SPREAD) && price <= 0)
    {
        QMessageBox::warning(this,_ApiPointer->getBaseWrapper()->getFileName(),"Price must be greater than zero");
        if(isSingleRowSelected)
            ui->doubleSpinBoxPrice->setValue(resetPrice.toDouble());
        return;
    }
    apiBookParams->cancelOrModify = ModificationIndex_ORDER_MODIFY;
    apiBookParams->orderId = orderIds.toStdString();

    _ApiPointer->getBaseWrapper()->modifyCancelOrders(strategyId,apiBookParams);
    enableParams(false);
}

void apiOrderBook::on_pushButtonCancel_clicked()
{
    QModelIndexList indexList = ui->apiOrderBookTableView->selectionModel()->selectedRows();
    if(!(indexList.size()))
    {
        QMessageBox::warning(this,_ApiPointer->getBaseWrapper()->getFileName(),"No row selected");
        return;
    }
    QHash<qlonglong,QString> hashStrategyIdOrderIds;
    qlonglong strategyId = 0;
    QModelIndex index;
    foreach (QModelIndex proxyIndex, indexList)
    {
        index = _proxyModel->mapToSource(proxyIndex);
        if(!index.isValid())
            continue;
        strategyId = _apiOrderBookModel->item(index.row(),colOrderBook_strategyId)->data(Qt::DisplayRole).toLongLong();
        hashStrategyIdOrderIds[strategyId] += _apiOrderBookModel->item(index.row(),colOrderBook_OrderId)->data(Qt::DisplayRole).toString() + ":";
    }

    short counter = 0;
    foreach (qlonglong key, hashStrategyIdOrderIds.keys())
    {
        if(!((++counter)%100))
        {
            counter = 0;
            qApp->processEvents();
        }
        hashStrategyIdOrderIds[key].chop(1);
        apiBookParams->orderQty = 0 ;
        apiBookParams->orderPrice=0;
        apiBookParams->orderId = hashStrategyIdOrderIds[key].toStdString();
        apiBookParams->cancelOrModify = ModificationIndex_ORDER_CANCEL;

        _ApiPointer->getBaseWrapper()->modifyCancelOrders(key, apiBookParams);
    }
}

bool apiOrderBook::isEnableState()
{
    return ui->spinBoxQty->isEnabled();
}

void apiOrderBook::setMoveProperty()
{
    move(parentWidget()->window()->frameGeometry().topLeft() +
                        parentWidget()->window()->rect().center() -
                             rect().center());
}

apiOrderBook::~apiOrderBook()
{
    _orderBookTimer.stop();
    DELETE_PTR(_proxyModel);
    DELETE_PTR(_headerView);
    DELETE_PTR(_shortCutFilter);
    DELETE_PTR(apiBookParams);
    delete _contextMenu;
    delete ui;
}
