#include <rawfx/core/composite.h>

namespace rawfx {
namespace core {

void composite::on(const event& evt, engine& eng) {
    if (evt.is(ATTACH)) {
        _engine = &eng;
    }

//        std::remove_if(children.begin(), children.end(), [](it) {
//            handler& h = it->get();
//            (*it)->on(evt, eng);
//            if ()

//        });

//        for (auto it = children.begin(); it != children.end(); it++) {
//            it->on(evt, eng);
//            if (eng.must_kill()) {

//            }
//            if ((*it)->is_dead()) {
//                // call detach
//                // delete (*it)
//                // remove from children vector
//            }
//        }
    if (evt.is(DETACH)) {
        _engine = nullptr;
    }
}

void composite::add(handler* h) {
    children.push_back(std::unique_ptr<handler>(h));
    if (_engine != nullptr) {
        h->on(ATTACH, *_engine);
    }
}

}
}
