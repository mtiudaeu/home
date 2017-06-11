#!/usr/bin/env python

#FIXME remove hardcoded output.dot
def generate_node_list_filter(filter_str):
    import subprocess
    p1 = subprocess.Popen(["cat", "output.dot"], stdout=subprocess.PIPE)
    p2 = subprocess.Popen(["grep", filter_str], stdin=p1.stdout, stdout=subprocess.PIPE)
    p3 = subprocess.Popen(["tr", "[", " "], stdin=p2.stdout, stdout=subprocess.PIPE)
    p4 = subprocess.Popen(["awk", "{print $1}"], stdin=p3.stdout, stdout=subprocess.PIPE)
    p5 = subprocess.Popen(["xargs", "echo"], stdin=p4.stdout, stdout=subprocess.PIPE)
    return p5.communicate()[0]

nodes_to_remove_str = generate_node_list_filter("green")
nodes_to_remove_str = nodes_to_remove_str + " " + generate_node_list_filter("\.so")
nodes_to_remove_str = nodes_to_remove_str + " " + generate_node_list_filter("\.o")
bad_node_lists = nodes_to_remove_str.split()

bad_node_lists = [bad_node+" " for bad_node in bad_node_lists]
bad_node_lists.append("green")
bad_node_lists.append(".so")
bad_node_lists.append(".o")

with open("output.dot") as oldfile, open('output_clean.dot', 'w') as newfile:
    for line in oldfile:
        if not any(bad_node in line for bad_node in bad_node_lists):
            newfile.write(line)





