namespace config = Util::config;

namespace NLP {
  namespace CRF {

    template <typename TAGGER>
    int run_train(int argc, char **argv, const char *IFMT, const char *TRAINER) {
      std::string preface;
      create_preface(argc, argv, preface);

      config::Main cfg(TAGGER::name, TAGGER::desc);
      typename TAGGER::Config tagger_cfg;
      Types types;

      config::OpAlias model(cfg, "model", "location to store the model", false, tagger_cfg.model);
      config::OpAlias sigma(cfg, "sigma", "sigma value for regularization", false, tagger_cfg.sigma);
      config::Op<std::string> ifmt(cfg, "ifmt", "input file format", IFMT, false, true);
      config::OpRestricted<std::string> trainer(cfg, "trainer", "training algorithm to use", TRAINER, "lbfgs|sgd", false, '|');

      tagger_cfg.add(&types);
      cfg.add(&tagger_cfg);
      if (cfg.process(argc, argv)) {
        Util::port::make_directory(tagger_cfg.model());
        TAGGER tagger(tagger_cfg, types, preface);
        ReaderFactory reader(TAGGER::reader, cfg.input(), cfg.input.file(), ifmt());
        tagger.train(reader, trainer());
      }

      return 0;
    }

    template <typename TAGGER>
    int run_tag(int argc, char **argv, const char *IFMT, const char *OFMT) {
      std::string preface;
      create_preface(argc, argv, preface);

      config::Main cfg(TAGGER::name, TAGGER::desc);
      typename TAGGER::Config tagger_cfg;
      Types types;

      config::OpAlias model(cfg, "model", "location of the model", false, tagger_cfg.model);
      config::Op<std::string> ifmt(cfg, "ifmt", "input file format", IFMT, false, true);
      config::Op<std::string> ofmt(cfg, "ofmt", "output file format", OFMT, false, true);

      tagger_cfg.add(&types);
      cfg.add(&tagger_cfg);

      if(cfg.process(argc, argv)) {
        TAGGER tagger(tagger_cfg, types, preface);
        ReaderFactory reader(TAGGER::reader, cfg.input(), cfg.input.file(), ifmt());
        WriterFactory writer("format", cfg.output(), cfg.output.file(), ofmt());
        tagger.run_tag(reader, writer);
      }

      return 0;
    }

    template <typename TAGGER>
    int run_train_factorial(int argc, char **argv, const char *IFMT, const char *CHAINS, const char *TRAINER) {
      std::string preface;
      create_preface(argc, argv, preface);

      config::Main cfg(TAGGER::name, TAGGER::desc);
      typename TAGGER::Config tagger_cfg;
      Types types;

      config::OpAlias model(cfg, "model", "location to store the model", false, tagger_cfg.model);
      config::OpAlias sigma(cfg, "sigma", "sigma value for regularization", false, tagger_cfg.sigma);
      config::Op<std::string> chains(cfg, "chains", "input chains", CHAINS, false, true);
      config::Op<std::string> ifmt(cfg, "ifmt", "input file format", IFMT, false, true);
      config::OpRestricted<std::string> trainer(cfg, "trainer", "training algorithm to use", TRAINER, "lbfgs|sgd|loopy_bp", false, '|');

      tagger_cfg.add(&types);
      cfg.add(&tagger_cfg);
      if (cfg.process(argc, argv)) {
        Util::port::make_directory(tagger_cfg.model());
        TAGGER tagger(tagger_cfg, types, chains(), preface);
        ReaderFactory reader(TAGGER::reader, cfg.input(), cfg.input.file(), ifmt());
        tagger.train(reader, trainer());
      }

      return 0;
    }

    template <typename TAGGER>
    int run_tag_factorial(int argc, char **argv, const char *IFMT, const char *OFMT,  const char *CHAINS) {
      std::string preface;
      create_preface(argc, argv, preface);

      config::Main cfg(TAGGER::name, TAGGER::desc);
      typename TAGGER::Config tagger_cfg;
      Types types;

      config::OpAlias model(cfg, "model", "location of the model", false, tagger_cfg.model);
      config::Op<std::string> ifmt(cfg, "ifmt", "input file format", IFMT, false, true);
      config::Op<std::string> ofmt(cfg, "ofmt", "output file format", OFMT, false, true);
      config::Op<std::string> chains(cfg, "chains", "output chains", CHAINS, false, true);

      tagger_cfg.add(&types);
      cfg.add(&tagger_cfg);

      if(cfg.process(argc, argv)) {
        TAGGER tagger(tagger_cfg, types, chains(), preface);
        ReaderFactory reader(TAGGER::reader, cfg.input(), cfg.input.file(), ifmt());
        WriterFactory writer("format", cfg.output(), cfg.output.file(), ofmt());
        tagger.run_tag(reader, writer);
      }

      return 0;
    }
  }
}
