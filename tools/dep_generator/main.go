// TODO
// 
// (per line)
// - Detect include line
// - Extract dependency
// 
// (per file)
// - Populate dependency tree
//
// (export to file)
// - Export to specefic tree format file (graphwiz)
//

package main

import (
	"bufio"
	"bytes"
	"flag"
	"io/ioutil"
	"log"
	"os"
	"path/filepath"
"strings"
)

func extractDependencies(line string) error {
  if(strings.Contains(line, "#include")) {
    log.Println(line)
  }
  return nil
}

func visitFunc(path string, f os.FileInfo, err error) error {
	data, err := ioutil.ReadFile(path)
	if err != nil {
		log.Println(err)
		return nil
	}

	scanner := bufio.NewScanner(bytes.NewReader(data))
	scanner.Split(bufio.ScanLines)
	for scanner.Scan() {
		extractDependencies(scanner.Text())
  if err != nil {
   log.Panic(err)
   return nil
  }
	}

	return nil
}

func main() {
	working_dir, err := os.Getwd()
	if err != nil {
		log.Panic(err)
	}

	root_dir := flag.String("p", working_dir, "")
	flag.Parse()

	err = filepath.Walk(*root_dir, visitFunc)
	if err != nil {
		log.Panic("filepath.Walk() returned ", err)
	}
}
