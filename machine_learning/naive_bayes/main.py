import re
import os

def clean_text(string):
  string = re.sub(r"[^A-Za-z0-9(),!?\'\`]", " ", string)
  string = re.sub(r"\'s", " \'s", string)
  string = re.sub(r"\'ve", " \'ve", string)
  string = re.sub(r"n\'t", " n\'t", string)
  string = re.sub(r"\'re", " \'re", string)
  string = re.sub(r"\'d", " \'d", string)
  string = re.sub(r"\'ll", " \'ll", string)
  string = re.sub(r",", " , ", string)
  string = re.sub(r"!", " ! ", string)
  string = re.sub(r"\(", " \( ", string)
  string = re.sub(r"\)", " \) ", string)
  string = re.sub(r"\?", " \? ", string)
  string = re.sub(r"\s{2,}", " ", string)
  return string.strip().lower()

class Classifier:
    def __init__(self, num_class):
        self.total_token_cnt = 0
        self.token_cnt_map = {}
        # map of map
        self.class_token_cnt_map = {}
        self.class_cnt_map = {}
        for cls in range(num_class):
            self.class_token_cnt_map[cls] = {}
            self.class_cnt_map[cls] = 0

    def parse(self, filename, label):
        line_cnt = 0
        with open(filename, "r") as fd:
            for line in fd.readlines():
                line_cnt += 1
                # if line_cnt % 1000 == 0:
                #     print "deal lines: %s" % line_cnt

                line = clean_text(line)
                line = line.strip()
                tokens = line.split()
                for token in tokens:
                    if token in self.token_cnt_map:
                        self.token_cnt_map[token] += 1
                    else:
                        self.token_cnt_map[token] = 1

                    class_token_cnt_map = self.class_token_cnt_map[int(label)]
                    if token in class_token_cnt_map:
                        class_token_cnt_map[token] += 1
                    else:
                        class_token_cnt_map[token] = 1
                    #if token == "laddish":
                    #    print "found laddish, label:", label
                    #    print self.class_token_cnt_map[int(label)]["laddish"]

                    self.class_cnt_map[int(label)] += 1
                    self.total_token_cnt += 1

    def count2prob(self):
        for token in self.token_cnt_map.keys():
            self.token_cnt_map[token] += 0.0
            self.token_cnt_map[token] /= self.total_token_cnt

        for label in self.class_token_cnt_map.keys():
            class_cnt = self.class_cnt_map[label]
            class_token_cnt_map = self.class_token_cnt_map[label]
            for token in class_token_cnt_map.keys():
                class_token_cnt_map[token] += 0.0
                class_token_cnt_map[token] /= class_cnt

    def calculate(self, tokens, label):
        p_c = self.class_cnt_map[label]*1.0 / self.total_token_cnt
        ratio = 1
        for token in tokens:
            if token in self.token_cnt_map:
                p_d = self.token_cnt_map[token]
            else:
                p_d = 1e-20

            if token in self.class_token_cnt_map[label]:
                p_d_c = self.class_token_cnt_map[label][token]
            else:
                p_d_c = 1e-20
            ratio *= (p_d_c/p_d)
            #ratio *= p_d_c
        prob = ratio * p_c
        return prob


    def predict(self, line):
        line = clean_text(line)
        line = line.strip()
        tokens = line.split()
        neg_prob = self.calculate(tokens, 0)
        pos_prob = self.calculate(tokens, 1)
        return (neg_prob, pos_prob)


classifier = Classifier(2)
classifier.parse("rt-polarity.neg", 0)
classifier.parse("rt-polarity.pos", 1)
classifier.count2prob()

print classifier.class_cnt_map
print classifier.total_token_cnt

correct = 0
wrong = 0
#with open("rt-polarity.neg", "r") as fd:
with open("neg.test", "r") as fd:
    for line in fd.readlines():
        #print line
        neg, pos = classifier.predict(line)
        if neg > pos:
            correct += 1
        else:
            wrong += 1
print correct, wrong

correct = 0
wrong = 0
#with open("rt-polarity.pos", "r") as fd:
with open("pos.test", "r") as fd:
    for line in fd.readlines():
        #print line
        neg, pos = classifier.predict(line)
        if neg < pos:
            correct += 1
        else:
            wrong += 1
print correct, wrong