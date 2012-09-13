#include "base.h"
#include "hashtable.h"
#include "crf/features/type.h"
#include "crf/features/context.h"
#include "crf/features/feature.h"
#include "crf/features/attributes.h"
#include "crf/features/feature_gen.h"

namespace NLP { namespace CRF {

WordGen::WordGen(const Type &type) : FeatureGen(type) { }

void WordGen::operator()(Attributes &attributes, Sentence &sent, TagPair &tp, int j) {
  if (tp.curr.id() != 1) {
    Raw word = sent.words[j];
    attributes(type.id, word, tp);
  }
}

void WordGen::operator()(Attributes &attributes, Sentence &sent, Context &c, int j) {
}


} }
