#!/bin/sh
ROOT=`git rev-parse --show-toplevel`
rm "${ROOT}/doc/docs.html"
rm -r "${ROOT}/doc/docs"
doxygen "${ROOT}/doc/.doxyfile"
ln -rs "${ROOT}/doc/docs/html/index.html" "${ROOT}/doc/docs.html"