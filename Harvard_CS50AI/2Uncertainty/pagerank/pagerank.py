import os
import random
import re
import sys

DAMPING = 0.85
SAMPLES = 10000


def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: python pagerank.py corpus")
    corpus = crawl(sys.argv[1])
    ranks = sample_pagerank(corpus, DAMPING, SAMPLES)
    print(f"PageRank Results from Sampling (n = {SAMPLES})")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")
    ranks = iterate_pagerank(corpus, DAMPING)
    print(f"PageRank Results from Iteration")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")


def crawl(directory):
    """
    Parse a directory of HTML pages and check for links to other pages.
    Return a dictionary where each key is a page, and values are
    a list of all other pages in the corpus that are linked to by the page.
    """
    pages = dict()

    # Extract all links from HTML files
    for filename in os.listdir(directory):
        if not filename.endswith(".html"):
            continue
        with open(os.path.join(directory, filename)) as f:
            contents = f.read()
            links = re.findall(r"<a\s+(?:[^>]*?)href=\"([^\"]*)\"", contents)
            pages[filename] = set(links) - {filename}

    # Only include links to other pages in the corpus
    for filename in pages:
        pages[filename] = set(
            link for link in pages[filename]
            if link in pages
        )

    return pages


def transition_model(corpus, page, damping_factor):
    """
    Return a probability distribution over which page to visit next,
    given a current page.

    With probability `damping_factor`, choose a link at random
    linked to by `page`. With probability `1 - damping_factor`, choose
    a link at random chosen from all pages in the corpus.
    """
    link = corpus[page]
    prob = dict()
    if len(link) == 0:
        for i in corpus:
            prob[i] = 1 / len(corpus)
        return prob
    for i in corpus:
        prob[i] = (1 - damping_factor) / len(corpus)
    for i in link:
        prob[i] += damping_factor / len(link)
    return prob


def sample_pagerank(corpus, damping_factor, n):
    """
    Return PageRank values for each page by sampling `n` pages
    according to transition model, starting with a page at random.

    Return a dictionary where keys are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """
    page = random.choice(list(corpus.keys()))
    prob = transition_model(corpus, page, damping_factor)
    ranks = dict()
    ranks[page] = ranks.get(page, 0) + 1
    for i in range(n - 1):
        page = random.choices(list(prob.keys()), list(prob.values()), k=1)[0]
        ranks[page] = ranks.get(page, 0) + 1
        prob = transition_model(corpus, page, damping_factor)
    for i in ranks:
        ranks[i] /= n
    return ranks


def iterate_pagerank(corpus, damping_factor):
    """
    Return PageRank values for each page by iteratively updating
    PageRank values until convergence.

    Return a dictionary where keys are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """
    prob = dict()
    for i in corpus:
        prob[i] = 1 / len(corpus)
    while True:
        ranks = dict()
        for it in prob.keys():
            ranks[it] = (1 - damping_factor) / len(corpus)
            temp = 0.0
            for page in corpus.keys():
                if it in corpus[page]:
                    temp += prob[page]/len(corpus[page])
                elif len(corpus[page]) == 0:
                    temp += prob[page]/len(corpus)
            ranks[it] += damping_factor * temp
        if all(abs(ranks[i] - prob[i]) <= 0.001 for i in prob.keys()):
            # print(f"iterate check : {sum(ranks.values())}")
            return ranks
        prob = ranks


if __name__ == "__main__":
    main()
