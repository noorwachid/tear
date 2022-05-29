#include "Sequence.h"
#include "SequenceDatabase.h"

namespace Tear {
    void Sequence::compose(const std::string& term) {
        SequenceDatabase database(term);
        mode = database.composeMode();
        command = database.composeCommand();
        key = database.composeKey();
    }
}