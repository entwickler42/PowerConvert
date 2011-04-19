#include "emathlistmodel.h"
#include <QList>
#include <QHash>
#include <emsi.h>
#include <emath.h>

const int UnitNameRole = Qt::UserRole + 1;
const int UnitValueRole = Qt::UserRole + 2;

EmathListModel::EmathListModel(QObject *parent) :
    QAbstractListModel(parent),
    m_freq(1000.0),
    m_gain(0.0),
    m_value(0.0)
{
	m_data = new QList<const struct emu_entry*>();	
	
	m_data->push_back(emu_find(EMU_WATT));
	m_data->push_back(emu_find(EMU_WM2));
	m_data->push_back(emu_find(EMU_WCM2));
	m_data->push_back(emu_find(EMU_VOLT));
	m_data->push_back(emu_find(EMU_VM));
	m_data->push_back(emu_find(EMU_DBVM));
	m_data->push_back(emu_find(EMU_DBUVM));
	//m_data->push_back(emu_find(EMU_AMPERE));
	m_data->push_back(emu_find(EMU_AM));
	
	QHash<int,QByteArray> roles = roleNames();
    roles.insert(UnitNameRole, QByteArray("UnitName"));
    roles.insert(UnitValueRole, QByteArray("UnitValue"));
    setRoleNames(roles);	
}

EmathListModel::~EmathListModel()
{
	delete m_data;
}

int EmathListModel::columnCount(const QModelIndex &parent) const
{			
	return 2;
}

int EmathListModel::rowCount(const QModelIndex &parent) const
{
	return m_data->count();
}

void EmathListModel::calculate(int index, double& result, QString& suffix) const
{
	const struct emu_entry* unit = m_data->at(index);		
	
	emconv(m_value, EMU_DBM, &result, unit->emu, 50.0, m_gain, uint64_t(m_freq) * 1000000llu);
	if( unit->db_type == EM_NOTDB ){
		if( const struct emsi_unit* scale = emsi_find_scale(result, 1.0) ){
			result /= scale->factor;
			suffix = QString("%1%2")
			        .arg(QString::fromWCharArray(scale->suffix))
			        .arg(QString::fromWCharArray(unit->suffix));
		}
	}else{
		suffix = QString::fromWCharArray(unit->suffix); 
	}
}

QVariant EmathListModel::data(const QModelIndex &index, int role) const
{	
	if( index.row() > m_data->count() -1 )
		return QVariant();
	if( !index.isValid() )
		return QVariant();
	
	QString suffix;
	double result;
	calculate(index.row(), result, suffix);
	
	switch( role )
	{
	case Qt::DisplayRole:
		switch( index.column() )
		{
		case 0:
			return QVariant(suffix);
		case 1:
			return QVariant(QString::number(result, 'f', 6));
		        default:
			        return QVariant();		
		}
		
	case UnitNameRole:
		return QVariant(suffix);		
		
	case UnitValueRole:
		return QVariant(QString::number(result, 'f', 6));
		
	default:
		return QVariant();
	}
	
	return QVariant();
}
