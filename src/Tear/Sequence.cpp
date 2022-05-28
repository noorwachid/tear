#include "Sequence.h"
#include "SequenceDatabase.h"

namespace Tear 
{
    void Sequence::Compose(const std::string& term) 
    {
        SequenceDatabase database(term);
        mode = database.ComposeMode();
        command = database.ComposeCommand();
        key = database.ComposeKey();
    }
}