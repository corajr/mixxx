#include <QSet>

#include "lastfm/lastfmclient.h"
#include "track/tagutils.h"

double TagUtils::jaccardSimilarity(const TagCounts& tags1,
                                   const TagCounts& tags2) {
    int iTagIntersection = 0;
    int iTagUnion = 0;
    QSet<QString> keys = QSet<QString>::fromList(tags1.keys());
    QSet<QString> keys2 = QSet<QString>::fromList(tags2.keys());
    keys.unite(keys2);
    for (QSet<QString>::const_iterator it = keys.constBegin();
         it != keys.constEnd(); ++it)  {
        QString key = *it;
        int count1 = tags1.value(key);
        int count2 = tags2.value(key);
        iTagIntersection += std::min(count1, count2);
        iTagUnion += count1 + count2;
    }
    return iTagUnion > 0 ? double(iTagIntersection)/iTagUnion : 0.0;
}
