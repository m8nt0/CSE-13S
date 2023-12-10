Mikias Berhane
December 9 2023
CSE 13-S

                                                            How to Compile for Web Crawler

Description:

The Web crawler is a standalone program that crawls the web and retrieves web pages starting from a “seed” URL. It parses the seed webpage, extracts any embedded URLs, then retrieves each of those pages, recursively, but limiting its exploration to a given “depth”.

Compile:

make (to compile)
make clean (clean up)
Then to run the program: ./crawler seedURL pageDirectory maxDepth



