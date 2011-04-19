#ifndef EMATHLISTMODEL_H
#define EMATHLISTMODEL_H

#include <QAbstractListModel>
#include <QMetaObject>

struct emu_entry;
template<class T> class QList;

class EmathListModel :
		public QAbstractListModel
{
	Q_OBJECT
	Q_PROPERTY( qreal frequency READ frequency WRITE setFrequency NOTIFY frequencyChanged )
	Q_PROPERTY( qreal gain READ gain WRITE setGain NOTIFY gainChanged )
	Q_PROPERTY( qreal value READ value WRITE setValue NOTIFY valueChanged )

signals:
	void frequencyChanged(qreal);
	void gainChanged(qreal);
	void valueChanged(qreal);

public:
	explicit EmathListModel(QObject *parent = 0);
	virtual ~EmathListModel();

	int columnCount(const QModelIndex &parent) const;
	int rowCount(const QModelIndex &parent) const;

	QVariant data(const QModelIndex &index, int role) const;

	qreal frequency() const
	{ return m_freq; }

	qreal gain() const
	{ return m_gain; }

	qreal value() const
	{ return m_value; }

public slots:
	void setFrequency(qreal frequency)
	{ m_freq = frequency; reset(); }

	void setGain(qreal gain)
	{ m_gain = gain; reset(); }

	void setValue(qreal value)
	{ m_value = value; reset(); }

private:
	QList<const struct emu_entry*>* m_data;
	void calculate(int index, double& result, QString& suffix) const;
	qreal m_freq;
	qreal m_gain;
	qreal m_value;
};

#endif // EMATHLISTMODEL_H
