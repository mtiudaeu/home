package main

import (
	"bufio"
	"bytes"
	"flag"
	"io/ioutil"
	"log"
	"os"
	"path/filepath"
	"strconv"
	"strings"
)

var static_output_map = make(map[string][]string)
var static_node_count = 0
var static_node_map = make(map[string]int)
var static_root_dir string

func writeGraphToFile(graph_str string) {
	filename := "dep_output.dot"
	err := ioutil.WriteFile(filename, []byte(graph_str), 0644)
	if err != nil {
		log.Panic(err)
		return
	}

}

func getNodeIdGraph(node_name string, graph_str *string) int {
	if node_id, ok := static_node_map[node_name]; ok {
		// nothing to add
		return node_id
	}
	static_node_count++
	static_node_map[node_name] = static_node_count
	*graph_str += "n" + strconv.Itoa(static_node_count) + "[label=\"" + node_name + "\", color=\"green\"];\n"

	return static_node_count
}

func generateDependencieGraph() string {
	var graph_str string
	// start graph
	graph_str += "digraph G {\n"

	for key, value := range static_output_map {
		key_node_id := getNodeIdGraph(key, &graph_str)
		for _, element := range value {
			element_node_id := getNodeIdGraph(element, &graph_str)
			graph_str += "n" + strconv.Itoa(element_node_id) + " -> n" + strconv.Itoa(key_node_id) + ";\n"
		}
	}
	// close graph
	graph_str += "}"
	return graph_str
}

func lineDetectDependencie(line string) bool {

	if strings.Contains(line, "#include") {
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
	tmp := strings.Replace(split_str[1], "\"", "", -1)
	tmp = strings.Replace(tmp, "<", "", -1)
	tmp = strings.Replace(tmp, ">", "", -1)
	return tmp
}

func acceptFilenameFilter(path string) bool {
	ext := filepath.Ext(path)
	return ext == ".cpp" ||
		ext == ".c" ||
		ext == ".C" ||
		ext == ".h" ||
		ext == ".hpp"
}

func visitFunc(path string, f os.FileInfo, err error) error {
	//MDTMP check if file
	if !acceptFilenameFilter(path) {
		return nil
	}
	//MDTMP check if name filter
	data, err := ioutil.ReadFile(path)
	if err != nil {
		// log.Panic(err)
		return nil
	}

	//FIXME + "/" HHHACK!!
	relative_path := strings.TrimPrefix(path, static_root_dir+"/")
	scanner := bufio.NewScanner(bytes.NewReader(data))
	scanner.Split(bufio.ScanLines)
	for scanner.Scan() {
		if lineDetectDependencie(scanner.Text()) {
			ret := lineExtractDependencie(scanner.Text())
			static_output_map[relative_path] = append(static_output_map[relative_path], ret)
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

	static_root_dir = *root_dir
	err = filepath.Walk(static_root_dir, visitFunc)
	if err != nil {
		log.Panic("filepath.Walk() returned ", err)
	}

	graph_str := generateDependencieGraph()

	writeGraphToFile(graph_str)
	//MDTMP log.Printf(graph_str)
}
