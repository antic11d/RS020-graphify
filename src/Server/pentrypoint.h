#ifndef PENTRYPOINT_H
#define PENTRYPOINT_H

#include "entity.h"
#include "edge.h"

#include <QObject>
#include <QVector>
#include <QString>

class PEntryPoint : public Entity
{
    Q_OBJECT
public:
    explicit PEntryPoint(QString key, QString value, QPointer<Metadata> metadata = nullptr, QObject *parent = nullptr);
    ~PEntryPoint();
private:
    QVector<Edge*> m_edges;
};

#endif // PENTRYPOINT_H
