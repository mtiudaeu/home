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
	//"fmt"
	"strings"
)

var static_output_map = make(map[string][]string)

func lineDetectDependencie(line string) bool {

	if strings.Contains(line, "#include") &&
		!strings.Contains(line, "<") {
		return true
	}
	return false
}

func lineExtractDependencie(line string) string {
	// Assumed line format : (#include "file/path.h")
	split_str := strings.Split(line, " ")
	if len(split_str) != 2 {
		//MDTMP error
		return ""
	}
	return split_str[1]
}

//MDTMP make(map[string][]string)
func visitFunc(path string, f os.FileInfo, err error) error {
	data, err := ioutil.ReadFile(path)
	if err != nil {
		// log.Panic(err)
		return nil
	}

	scanner := bufio.NewScanner(bytes.NewReader(data))
	scanner.Split(bufio.ScanLines)
	for scanner.Scan() {
		if lineDetectDependencie(scanner.Text()) {
			ret := lineExtractDependencie(scanner.Text())
			static_output_map[path] = append(static_output_map[path], ret)
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

	for key, value := range static_output_map {
		for _, element := range value {
   log.Println(key, element)
		}
	}
}
