import rdflib
from rdflib.Graph import Graph

# TODO : improve namespace usage
rdf_type = rdflib.URIRef('http://www.w3.org/1999/02/22-rdf-syntax-ns#type')
lv2_ControlPort = rdflib.URIRef('http://lv2plug.in/ns/lv2core#ControlPort')
lv2_index = rdflib.URIRef('http://lv2plug.in/ns/lv2core#index')
lv2_symbol = rdflib.URIRef('http://lv2plug.in/ns/lv2core#symbol')
lv2_name = rdflib.URIRef('http://lv2plug.in/ns/lv2core#name')
lv2_minimum = rdflib.URIRef('http://lv2plug.in/ns/lv2core#minimum')
lv2_maximum = rdflib.URIRef('http://lv2plug.in/ns/lv2core#maximum')
lv2_default = rdflib.URIRef('http://lv2plug.in/ns/lv2core#default')

ext_step = rdflib.URIRef('http://www.westkamper.com/lv2/ext#step')

meta_cpp = []
meta_cpp.append("#ifndef ANALOGUE_META")
meta_cpp.append("#define ANALOGUE_META\n")

meta_cpp.append("typedef struct {")
meta_cpp.append("  const char *symbol;")
meta_cpp.append("  const char *name;")
meta_cpp.append("  float min;")
meta_cpp.append("  float max;")
meta_cpp.append("  float default_value;")
meta_cpp.append("  float step;")
meta_cpp.append("} port_meta_t;\n")

meta_cpp.append("static const port_meta_t p_port_meta[] = {")

g = Graph()
g.parse("analogue.ttl", format="n3")
maxIndex = 0

for i in g.objects(None, lv2_index):
    maxIndex = max(maxIndex, i.toPython())

for i in range(3, maxIndex + 1):
    p = g.subjects(lv2_index, rdflib.Literal(i)).next() 
    symbol = g.objects(p, lv2_symbol).next()
    name = g.objects(p, lv2_name).next()
    minimum = g.objects(p, lv2_minimum).next().toPython()
    maximum = g.objects(p, lv2_maximum).next().toPython()
    default = g.objects(p, lv2_default).next().toPython()
    step = g.objects(p, ext_step).next().toPython()

    meta_cpp.append('  {"%s", "%s", %s, %s, %s, %s},' % (symbol, name, minimum, maximum, default, step))

meta_cpp.append("};")
meta_cpp.append("#endif")

cppFile = open("gen/analogue-meta.h", "w")
cppFile.write("\n".join(meta_cpp))
cppFile.close()

