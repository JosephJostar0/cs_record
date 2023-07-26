import nltk
import sys
import pathlib
import string
import math
import os
import platform

FILE_MATCHES = 1
SENTENCE_MATCHES = 1


def main():

    # Check command-line arguments
    if len(sys.argv) != 2:
        sys.exit("Usage: python questions.py corpus")

    # Calculate IDF values across files
    files = load_files(sys.argv[1])
    file_words = {
        filename: tokenize(files[filename])
        for filename in files
    }
    file_idfs = compute_idfs(file_words)

    # Prompt user for query
    query = set(tokenize(input("Query: ")))

    # Determine top file matches according to TF-IDF
    filenames = top_files(query, file_words, file_idfs, n=FILE_MATCHES)

    # Extract sentences from top files
    sentences = dict()
    for filename in filenames:
        for passage in files[filename].split("\n"):
            for sentence in nltk.sent_tokenize(passage):
                tokens = tokenize(sentence)
                if tokens:
                    sentences[sentence] = tokens

    # Compute IDF values across sentences
    idfs = compute_idfs(sentences)

    # Determine top sentence matches
    matches = top_sentences(query, sentences, idfs, n=SENTENCE_MATCHES)
    for match in matches:
        print(match)


def load_files(directory: str) -> dict:
    """
    Given a directory name, return a dictionary mapping the filename of each
    `.txt` file inside that directory to the file's contents as a string.
    """
    path = pathlib.Path(directory)
    if not path.exists() or not path.is_dir():
        raise ValueError('不存在该路径')
    fdic = dict()
    for file in path.iterdir():
        if file.is_file() and file.suffix == '.txt':
            with open(file, 'r', encoding='utf-8') as f:
                fdic[file.name] = f.read()
    return fdic


def tokenize(document: str) -> list:
    """
    Given a document (represented as a string), return a list of all of the words in that document, in order.

    Process document by coverting all words to lowercase, and removing any punctuation or English stopwords.
    """
    tokens = nltk.word_tokenize(document)
    tokens = [token.lower()
              for token in tokens if token not in string.punctuation and token not in nltk.corpus.stopwords.words('english')]
    return tokens


def compute_idfs(documents: dict) -> dict:
    """
    Given a dictionary of `documents` that maps names of documents to a list of words, return a dictionary that maps words to their IDF values.

    Any word that appears in at least one of the documents should be in the resulting dictionary.

    Recall that the inverse document frequency of a word is defined by taking the natural logarithm of the number of documents divided by the number of documents in which the word appears.
    """
    idfs = dict()
    word_set = set()
    for doc in documents.keys():
        word_set.clear()
        for word in documents[doc]:
            if word not in word_set:
                if word not in idfs.keys():
                    idfs[word] = 0
                word_set.add(word)
                idfs[word] += 1
    for word in idfs.keys():
        idfs[word] = len(documents) / idfs[word]
        idfs[word] = round(math.log(idfs[word]), 4)
    return idfs


def top_files(query: set, files: dict, idfs: dict, n: int) -> list:
    """
    Given a `query` (a set of words), `files` (a dictionary mapping names of files to a list of their words), and `idfs` (a dictionary mapping words to their IDF values), return a list of the filenames of the the `n` top files that match the query, ranked according to tf-idf.
    Recall that tf-idf for a term is computed by multiplying the number of times the term appears in the document by the IDF value for that term.
    """
    tf_idfs = dict()
    for file in files.keys():
        tf_idfs[file] = 0
        for word in query:
            tf_idfs[file] += files[file].count(word) * idfs[word]
    tf_idfs = sorted(tf_idfs.items(), key=lambda x: x[1], reverse=True)
    return [tf_idfs[i][0] for i in range(n)]


def top_sentences(query: set, sentences: dict, idfs: dict, n: int) -> list:
    """
    Given a `query` (a set of words), `sentences` (a dictionary mapping
    sentences to a list of their words), and `idfs` (a dictionary mapping words to their IDF values), return a list of the `n` top sentences that match the query, ranked according to idf. If there are ties, preference should be given to sentences that have a higher query term density.

    Sentences should be ranked according to “matching word measure”: namely, the sum of IDF values for any word in the query that also appears in the sentence. Note that term frequency should not be taken into account here, only inverse document frequency.
    If two sentences have the same value according to the matching word measure, then sentences with a higher “query term density” should be preferred. Query term density is defined as the proportion of words in the sentence that are also words in the query. For example, if a sentence has 10 words, 3 of which are in the query, then the sentence's query term density is 0.3.
    """
    def cmp(x):
        return x[1], sum([1 for word in query if word in x[0]]) / len(sentences[x[0]])

    tf_idfs = dict()
    for sentence in sentences.keys():
        tf_idfs[sentence] = 0
        for word in query:
            if word in sentences[sentence]:
                tf_idfs[sentence] += idfs[word]
    tf_idfs = sorted(tf_idfs.items(), key=cmp, reverse=True)
    return [tf_idfs[i][0] for i in range(n)]


if __name__ == "__main__":
    main()
