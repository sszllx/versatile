#include "exchange_sub_win.h"
#include "exchange_helper.h"

#include <QtWidgets>
#include <QDebug>
#include <QFile>
#include <QTextStream>

const QString URL="http://www.boc.cn/sourcedb/whpj/";
const double org_total_invest = 137000.00;
const double g_total_usd = 20000;

#define CHECK_INDEX(i) do { \
    if(i < 0) { \
        printf ("check failed!\n"); \
        return; \
    } \
}while(0);

ProgressDialog::ProgressDialog(const QString &url, QWidget *parent)
    : QProgressDialog(parent)
{
    setWindowTitle(tr("Download Progress"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setLabelText(tr("Downloading %1.").arg(url));
    setMinimum(0);
    setValue(0);
    setMinimumDuration(0);
}

void ProgressDialog::networkReplyProgress(qint64 bytesRead, qint64 totalBytes)
{
    setMaximum(totalBytes);
    setValue(bytesRead);
}

ExchangeWin::ExchangeWin(QWidget *parent)
    : QWidget(parent),
      m_helper(new ExchangeHelper(this))
{
    init();
    initUI();
}

void ExchangeWin::initUI()
{
    QSplitter *splitter = new QSplitter(this);

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    QHBoxLayout *item1_layout = new QHBoxLayout(this);
    QLabel *usd_label = new QLabel(this);
    usd_label->setText("USD:");
    m_usd_editor = new QTextEdit(this);
    //    splitter->addWidget(usd_label);
    //    splitter->addWidget(m_usd_editor);
    item1_layout->addWidget(usd_label);
    item1_layout->addWidget(m_usd_editor);

    QHBoxLayout *item2_layout = new QHBoxLayout(this);
    m_profit = new QTextEdit(this);
    QLabel *profit_label = new QLabel(this);
    profit_label->setText("Profit:");
    item2_layout->addWidget(profit_label);
    item2_layout->addWidget(m_profit);

    main_layout->addLayout(item1_layout);
    main_layout->addLayout(item2_layout);
    main_layout->addWidget(splitter);
    main_layout->addStretch(100);
}

void ExchangeWin::init()
{
    ProgressDialog *progressDialog = new ProgressDialog("download", this);
    progressDialog->setAttribute(Qt::WA_DeleteOnClose);
    connect(progressDialog, &QProgressDialog::canceled, m_helper, &ExchangeHelper::onCancelDownload);
    connect(m_helper, &ExchangeHelper::downloadProgress, progressDialog, &ProgressDialog::networkReplyProgress);
    connect(m_helper, &ExchangeHelper::finished, progressDialog, &ProgressDialog::hide);
    connect(m_helper, &ExchangeHelper::finished, this, &ExchangeWin::finished);
    progressDialog->setGeometry(400, 800, 200, 100);
    progressDialog->show();

    QUrl url(URL);
    m_helper->request(url);
}

void ExchangeWin::finished(QString content)
{
    if (content.isEmpty()) {
        qDebug() << "content is empty!";
        return;
    }

    int index = content.indexOf("DefaultMain");

    index = content.indexOf("<td>美元</td>", index);
    CHECK_INDEX(index);

    index = content.indexOf("<td>", index + 1);
    CHECK_INDEX(index);

    index = content.indexOf("<td>", index + 1);
    CHECK_INDEX(index);

    index = content.indexOf("<td>", index + 1);
    CHECK_INDEX(index);

    int start_index = content.indexOf(">", index);
    int end_index = content.indexOf("<", start_index);

    QString usd_value = content.mid(start_index + 1, end_index - start_index - 1);
    m_usd_editor->setText(usd_value);

    qDebug() << usd_value;

    double current_exch_rate = usd_value.toDouble() / 100;
    double tmp_value = g_total_usd * current_exch_rate;
    tmp_value = tmp_value - org_total_invest - 1000;
    if (tmp_value < 0) {
        m_profit->setTextColor(QColor(Qt::red));
    } else {
        m_profit->setTextColor(QColor(Qt::green));
    }
    m_profit->setText(QString("%1").arg(tmp_value));
}
