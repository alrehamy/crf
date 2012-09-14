#include "base.h"

#include "config.h"
#include "io.h"
#include "hashtable.h"
#include "lexicon.h"
#include "tagset.h"
#include "crf/features.h"
#include "crf.h"

namespace config = Util::config;

namespace NLP {

  template <typename TAGGER>
  int run_train(int argc, char **argv) {
    std::string preface;
    create_preface(argc, argv, preface);

    config::Main cfg(TAGGER::name, TAGGER::desc);
    typename TAGGER::Config tagger_cfg;

    config::OpAlias model(cfg, "model", "location to store the model", tagger_cfg.model);

    config::OpInput input(cfg, "input", "training data location");

    TAGGER tagger(tagger_cfg, preface);
    cfg.add(&tagger_cfg);
    cfg.add(&tagger.feature_types());
    if(cfg.process(argc, argv)) {
      ReaderFactory reader("conll", input(), input.file(), "");
      tagger.train(reader);
    }

    return 0;
  }
}
