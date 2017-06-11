#!/usr/bin/env python

#MDTMP remove hardcoded output.dot
#MDTMP Add a proper filter function (accept "green" ".so" ".o" etc...)
import subprocess
p1 = subprocess.Popen(["cat", "output.dot"], stdout=subprocess.PIPE)
p2 = subprocess.Popen(["grep", "green"], stdin=p1.stdout, stdout=subprocess.PIPE)
p3 = subprocess.Popen(["tr", "[", " "], stdin=p2.stdout, stdout=subprocess.PIPE)
p4 = subprocess.Popen(["awk", "{print $1}"], stdin=p3.stdout, stdout=subprocess.PIPE)
p5 = subprocess.Popen(["xargs", "echo"], stdin=p4.stdout, stdout=subprocess.PIPE)

nodes_to_remove = p5.communicate()[0]
bad_node_lists = nodes_to_remove.split()

bad_node_lists = [bad_node+" " for bad_node in bad_node_lists]
bad_node_lists.append("green")

with open("output.dot") as oldfile, open('output_clean.dot', 'w') as newfile:
    for line in oldfile:
        if not any(bad_node in line for bad_node in bad_node_lists):
            newfile.write(line)





