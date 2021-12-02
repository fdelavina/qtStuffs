#include <QtGui>
#include <QWidget>

#if defined TEST
#define TEST_COMMON_DLLSPEC Q_DECL_EXPORT
#else
#define TEST_COMMON_DLLSPEC Q_DECL_IMPORT
#endif

class TEST_COMMON_DLLSPEC Widget : public QWidget {

Q_OBJECT
public:

Widget();
};
