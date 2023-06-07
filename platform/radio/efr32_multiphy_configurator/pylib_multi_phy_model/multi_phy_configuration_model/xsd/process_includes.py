#!/usr/bin/env python
"""
    python %prog [options] <in_schema.xsd>  <out_schema.xsd>
Synopsis:
    Prepare schema document.  Replace include and import elements.
Examples:
    python %prog myschema.xsd
    python %prog myschema.xsd newschema.xsd
    python %prog -f myschema.xsd newschema.xsd
    cat infile.xsd | python %prog > outfile.xsd
"""

#
# Imports

import sys
import os
if sys.version_info.major == 2:
    import urllib2
else:
    import urllib.request
    import urllib.error
    import urllib.parse
import copy
from optparse import OptionParser, Values
import itertools
from copy import deepcopy
from lxml import etree

try:
    from gds_inner_name_map import Inner_name_map
except ImportError:
    Inner_name_map = None


#
# Globals and constants

#
# Do not modify the following VERSION comments.
# Used by updateversion.py.
##VERSION##
VERSION = '2.28a'
##VERSION##

CatalogDict = {}
# the base url to use for all relative paths in the catalog
CatalogBaseUrl = None


#
# Exceptions

class SchemaIOError(IOError):
    pass


class InnerNameMapError(Exception):
    pass


def load_catalog(catalogpath):
    global CatalogBaseUrl
    if catalogpath:
        CatalogBaseUrl = os.path.split(catalogpath)[0]
        catalog = etree.parse(open(catalogpath))
        for elements in catalog.getroot().findall(
                "{urn:oasis:names:tc:entity:xmlns:xml:catalog}public"):
            CatalogDict[elements.get("publicId")] = elements.get("uri")

#
# Functions for external use


def process_include_files(
        infile, outfile, inpath='',
        catalogpath=None,
        fixtypenames=None,
        no_collect_includes=False,
        no_redefine_groups=False):
    load_catalog(catalogpath)
    options = Values({
        'force': False,
        'fixtypenames': fixtypenames,
        'no_collect_includes': no_collect_includes,
        'no_redefine_groups': no_redefine_groups,
    })
    doc = prep_schema_doc(infile, outfile, inpath, options)
    return doc


def get_all_root_file_paths(
        infile,
        inpath='',
        catalogpath=None,
        shallow=False):
    load_catalog(catalogpath)
    doc1 = etree.parse(infile)
    root1 = doc1.getroot()
    rootPaths = []
    params = Params()
    params.parent_url = infile
    params.base_url = os.path.split(inpath)[0]
    get_root_file_paths(root1, params, rootPaths, shallow)
    rootPaths.append(inpath)
    return rootPaths


#
# Classes

class Params(object):
    members = ('base_url', 'already_processed', 'parent_url', )

    def __init__(self):
        self.base_url = None
        self.already_processed = set()
        self.parent_url = None

    def __setattr__(self, name, value):
        if name not in self.members:
            raise AttributeError('Class %s has no set-able attribute "%s"' % (
                self.__class__.__name__, name, ))
        self.__dict__[name] = value


#
# Functions for internal use and testing


def clear_includes_and_imports(node):
    namespace = node.nsmap[node.prefix]
    child_iter1 = node.iterfind('{%s}include' % (namespace, ))
    child_iter2 = node.iterfind('{%s}import' % (namespace, ))
    for child in itertools.chain(child_iter1, child_iter2):
        repl = etree.Comment(etree.tostring(child))
        repl.tail = '\n'
        node.replace(child, repl)


def get_ref_info(node, params):
    # first look for the schema location in the catalog, if not
    # there, then see if it's specified in the node
    namespace = node.get('namespace')
    url = None
    baseUrl = None
    if namespace in CatalogDict:
        url = CatalogDict[namespace]
        # setup the base url in case the path
        # in the catalog was a relative path
        baseUrl = CatalogBaseUrl
    if not url:
        url = node.get('schemaLocation')

    if not url:
        msg = '*** Warning: missing "schemaLocation" attribute in %s\n' % (
            params.parent_url, )
        sys.stderr.write(msg)
        return (None, None)
    # Uncomment the next lines to help track down missing schemaLocation etc.
    # print '(resolve_ref) url: %s\n    parent-url: %s' % (
    #     url, params.parent_url, )

    if not baseUrl:
        baseUrl = params.base_url

    if baseUrl and not (
            url.startswith('/') or
            url.startswith('http:') or
            url.startswith('ftp:')):
        locn = '%s/%s' % (baseUrl, url, )
        schema_name = locn
    else:
        locn = url
        schema_name = url

    return locn, schema_name


def resolve_ref(node, params, options):
    content = None

    locn, schema_name = get_ref_info(node, params)

    if locn is not None and not (
            locn.startswith('/') or
            locn.startswith('http:') or
            locn.startswith('ftp:')):
        schema_name = os.path.abspath(locn)
    if locn is not None:
        if schema_name not in params.already_processed:
            params.already_processed.add(schema_name)
##             print 'trace --'
##             print '    url:        : %s' % (url, )
##             print '    base        : %s' % (params.base_url, )
##             print '    parent      : %s' % (params.parent_url, )
##             print '    locn        : %s' % (locn, )
##             print '    schema_name : %s\n' % (schema_name, )
            if locn.startswith('http:') or locn.startswith('ftp:'):
                if sys.version_info.major == 2:
                    urllib_urlopen = urllib2.urlopen
                    urllib_httperror = urllib2.HTTPError
                else:
                    urllib_urlopen = urllib.request.urlopen
                    urllib_httperror = urllib.error.HTTPError
                try:
                    urlfile = urllib_urlopen(locn)
                    content = urlfile.read()
                    urlfile.close()
                    params.parent_url = locn
                    params.base_url = os.path.split(locn)[0]
                except urllib_httperror:
                    msg = "Can't find file %s referenced in %s." % (
                        locn, params.parent_url, )
                    raise SchemaIOError(msg)
            else:
                if os.path.exists(locn):
                    infile = open(locn)
                    unencoded_content = infile.read()
                    if sys.version_info.major == 2:
                        content = unencoded_content
                    else:
                        content = unencoded_content.encode()
                    infile.close()
                    params.parent_url = locn
                    params.base_url = os.path.split(locn)[0]
                if content is None:
                    msg = "Can't find file %s referenced in %s." % (
                        locn, params.parent_url, )
                    raise SchemaIOError(msg)
##     if content is None:
##         msg = "Can't find file %s referenced in %s." % (
##             locn, params.parent_url, )
##         raise SchemaIOError(msg)
    return content


def collect_inserts(node, params, inserts, options):
    namespace = node.nsmap[node.prefix]
    roots = []
    child_iter1 = node.iterfind('{%s}include' % (namespace, ))
    child_iter2 = node.iterfind('{%s}import' % (namespace, ))
    for child in itertools.chain(child_iter1, child_iter2):
        aux_roots = collect_inserts_aux(child, params, inserts, options)
        roots.extend(aux_roots)

    return roots


def collect_inserts_aux(child, params, inserts, options):
    roots = []
    save_base_url = params.base_url
    string_content = resolve_ref(child, params, options)
    if string_content is not None:
        root = etree.fromstring(string_content, base_url=params.base_url)
        roots.append(root)
        for child1 in root:
            if not isinstance(child1, etree._Comment):
                namespace = child1.nsmap[child1.prefix]
                if (child1.tag != '{%s}include' % (namespace, ) and
                        child1.tag != '{%s' % (namespace, )):
                    comment = etree.Comment(etree.tostring(child))
                    comment.tail = '\n'
                    inserts.append(comment)
                    inserts.append(child1)
        insert_roots = collect_inserts(root, params, inserts, options)
        roots.extend(insert_roots)
    params.base_url = save_base_url
    return roots


def get_root_file_paths(node, params, rootPaths, shallow):
    namespace = node.nsmap[node.prefix]
    child_iter1 = node.iterfind('{%s}include' % (namespace, ))
    child_iter2 = node.iterfind('{%s}import' % (namespace, ))
    for child in itertools.chain(child_iter1, child_iter2):
        get_root_file_paths_aux(child, params, rootPaths, shallow)


def get_root_file_paths_aux(child, params, rootPaths, shallow):
    save_base_url = params.base_url
    path, _ = get_ref_info(child, params)
    string_content = resolve_ref(child, params, None)
    if string_content is not None:
        if not shallow:
            root = etree.fromstring(string_content, base_url=params.base_url)
            get_root_file_paths(root, params, rootPaths, shallow)
    if path is not None and path not in rootPaths:
        rootPaths.append(path)
    params.base_url = save_base_url


def make_file(outFileName, options):
    outFile = None
    if (not options.force) and os.path.exists(outFileName):
        if sys.version_info.major == 3:
            raw_input = input
        reply = raw_input(
            'File %s exists.  Overwrite? (y/n): ' % outFileName)
        if reply == 'y':
            outFile = open(outFileName, 'w')
    else:
        outFile = open(outFileName, 'w')
    return outFile


def prep_schema_doc(infile, outfile, inpath, options):
    doc1 = etree.parse(infile)
    root1 = doc1.getroot()
    params = Params()
    params.parent_url = infile
    params.base_url = os.path.split(inpath)[0]
    inserts = []
    if not options.no_collect_includes:
        collect_inserts(root1, params, inserts, options)
        root2 = copy.copy(root1)
        clear_includes_and_imports(root2)
        for insert_node in inserts:
            root2.append(insert_node)
    else:
        root2 = root1
    if not options.no_redefine_groups:
        process_groups(root2)
    raise_anon_complextypes(root2)
    fix_type_names(root2, options)
    doc2 = etree.ElementTree(root2)
    if sys.version_info.major == 2:
        doc2.write(outfile)
    else:
        outfile.write(etree.tostring(root2).decode('utf-8'))
    return doc2


def prep_schema(inpath, outpath, options):
    if inpath:
        infile = open(inpath, 'r')
    else:
        infile = sys.stdin
    if outpath:
        outfile = make_file(outpath, options)
    else:
        outfile = sys.stdout
    if outfile is None:
        return
    prep_schema_doc(infile, outfile, inpath, options)
    if inpath:
        infile.close()
    if outpath:
        outfile.close()


def process_groups(root):
    # Get all the xs:group definitions at top level.
    if root.prefix:
        namespaces = {root.prefix: root.nsmap[root.prefix]}
        pattern = './%s:group' % (root.prefix, )
        defs = root.xpath(pattern, namespaces=namespaces)
    else:
        pattern = './group'
        defs = root.xpath(pattern)
    defs = [node for node in defs if node.get('name') is not None]
    # Get all the xs:group references (below top level).
    if root.prefix:
        namespaces = {root.prefix: root.nsmap[root.prefix]}
        pattern = './*//%s:group' % (root.prefix, )
        refs = root.xpath(pattern, namespaces=namespaces)
    else:
        pattern = './*//group'
        refs = root.xpath(pattern)
    refs = [node for node in refs if node.get('ref') is not None]
    # Create a dictionary of the named model groups (definitions).
    def_dict = {}
    for node in defs:
        def_dict[trim_prefix(node.get('name'))] = node
    replace_group_defs(def_dict, refs)


def fix_type_names(root, options):
    fixnamespec = options.fixtypenames
    if fixnamespec:
        namespecs = fixnamespec.split(';')
    else:
        namespecs = []
    for namespec in namespecs:
        names = namespec.split(':')
        if len(names) == 2:
            oldname = names[0]
            newname = names[1]
        elif len(names) == 1:
            oldname = names[0]
            newname = '%sxx' % (oldname, )
        else:
            continue
        # Change the name (name attribute) of the complexType.
        pat = './/%s:complexType[@name="%s"]' % (
            root.prefix, oldname)
        elements = xpath_find(root, pat)
        if len(elements) < 1:
            sys.stderr.write(
                "\nWarning: fix-type-names can't find complexType '%s'.  "
                "Exiting.\n\n" % (oldname, ))
            sys.exit(1)
        if len(elements) < 1:
            sys.stderr.write(
                "Warning: fix-type-names found more than "
                "one complexType '%s'.  "
                "Changing first." % (oldname, ))
        element = elements[0]
        element.set('name', newname)
        # Change the reference (type attribute) of child elements.
        pat = './/%s:element' % (root.prefix, )
        elements = xpath_find(root, pat)
        for element in elements:
            typename = element.get('type')
            if not typename:
                continue
            names = typename.split(':')
            if len(names) == 2:
                typename = names[1]
            elif len(names) == 1:
                typename = names[0]
            else:
                continue
            if typename != oldname:
                continue
            if not element.getchildren():
                element.set('type', newname)
        # Change the extensions ('base' attribute) that refer to the old type.
        pat = './/%s:extension' % (root.prefix, )
        elements = xpath_find(root, pat)
        for element in elements:
            typename = element.get('base')
            if not typename:
                continue
            names = typename.split(':')
            if len(names) == 2:
                typename = names[1]
            elif len(names) == 1:
                typename = names[0]
            else:
                continue
            if typename != oldname:
                continue
            element.set('base', newname)


def xpath_find(node, pat):
    namespaces = {node.prefix: node.nsmap[node.prefix]}
    elements = node.xpath(pat, namespaces=namespaces)
    return elements


def replace_group_defs(def_dict, refs):
    for ref_node in refs:
        name = trim_prefix(ref_node.get('ref'))
        if name is None:
            continue
        def_node = def_dict.get(name)
        namespaces = {def_node.prefix: def_node.nsmap[def_node.prefix]}
        if def_node is not None:
            pattern = './%s:sequence|./%s:choice|./%s:all' % (
                def_node.prefix, def_node.prefix, def_node.prefix, )
            content = def_node.xpath(
                pattern,
                namespaces=namespaces)
            if content:
                content = content[0]
                parent = ref_node.getparent()
                for node in content:
                    if not isinstance(node, etree._Comment):
                        new_node = deepcopy(node)
                        # Copy minOccurs and maxOccurs attributes to new node.
                        value = ref_node.get('minOccurs')
                        if value is not None:
                            new_node.set('minOccurs', value)
                        value = ref_node.get('maxOccurs')
                        if value is not None:
                            new_node.set('maxOccurs', value)
                        ref_node.addprevious(new_node)
                parent.remove(ref_node)


def raise_anon_complextypes(root):
    """ Raise each anonymous complexType to top level and give it a name.
    Rename if necessary to prevent duplicates.
    """
    def_names = collect_type_names(root)
    def_count = 0
    # Find all complexTypes below top level.
    #   Raise them to top level and name them.
    #   Re-name if there is a duplicate (simpleType, complexType, or
    #   previous renamed type).
    #   Change the parent (xs:element) so the "type" attribute refers to
    #   the raised and renamed type.
    #   Collect the new types.
    el = etree.Comment(text="Raised anonymous complexType definitions")
    el.tail = "\n\n"
    root.append(el)
    prefix = root.prefix
    if prefix:
        pattern = './*/*//%s:complexType|./*/*//%s:simpleType' % (
            prefix, prefix, )
        element_tag = '{%s}element' % (root.nsmap[prefix], )
        namespaces = {prefix: root.nsmap[prefix]}
        defs = root.xpath(pattern, namespaces=namespaces)
    else:
        pattern = './*/*//complexType|./*/*//simpleType'
        element_tag = 'element'
        defs = root.xpath(pattern)
    for node in defs:
        parent = node.getparent()
        if parent.tag != element_tag:
            continue
        name = parent.get('name')
        if not name:
            continue
        type_name = '%sType' % (name, )
        if Inner_name_map is None:
            type_name, def_count = unique_name(type_name, def_names, def_count)
        else:
            type_name = map_inner_name(node, Inner_name_map)
        def_names.add(type_name)
        parent.set('type', type_name)
        node.set('name', type_name)
        # Move the complexType node to top level.
        root.append(node)


def map_inner_name(node, inner_name_map):
    """Use a user-supplied mapping table to look up a name for this class/type.
    """
    # find the name for the enclosing type definition and
    # the name of the type definition that encloses that.
    node1 = node
    name2 = node1.get('name')
    while name2 is None:
        node1 = node1.getparent()
        if node1 is None:
            raise InnerNameMapError('cannot find parent with "name" attribute')
        name2 = node1.get('name')
    node1 = node1.getparent()
    name1 = node1.get('name')
    while name1 is None:
        node1 = node1.getparent()
        if node1 is None:
            raise InnerNameMapError('cannot find parent with "name" attribute')
        name1 = node1.get('name')
    new_name = inner_name_map.get((name1, name2))
    if new_name is None:
        msg1 = '("{}", "{}")'.format(
            name1, name2)
        sys.stderr.write('\n*** error.  Must add entry to inner_name_map:\n')
        sys.stderr.write('\n    {}: "xxxx",\n\n'.format(msg1))
        raise InnerNameMapError('mapping missing for {}'.format(msg1))
    return new_name


#
# Collect the names of all currently defined types (complexType,
#   simpleType, element).
def collect_type_names(node):
    prefix = node.prefix
    if prefix is not None and prefix.strip():
        pattern = './/%s:complexType|.//%s:simpleType|.//%s:element' % (
            prefix, prefix, prefix)
        # Must make sure that we have a namespace dictionary that does *not*
        # have a key None.
        namespaces = {prefix: node.nsmap[prefix]}
        elements = node.xpath(pattern, namespaces=namespaces)
    else:
        pattern = './/complexType|.//simpleType|.//element'
        elements = node.xpath(pattern)
    names = {
        el.attrib['name'] for el in elements if
        'name' in el.attrib and el.getchildren()
    }
    return names


def unique_name(type_name, def_names, def_count):
    orig_type_name = type_name
    while True:
        if type_name not in def_names:
            return type_name, def_count
        def_count += 1
        type_name = '%s%d' % (orig_type_name, def_count, )


def trim_prefix(name):
    names = name.split(':')
    if len(names) == 1:
        return names[0]
    elif len(names) == 2:
        return names[1]
    else:
        return None


USAGE_TEXT = __doc__


def usage(parser):
    parser.print_help()
    sys.exit(1)


def main():
    parser = OptionParser(USAGE_TEXT)
    parser.add_option(
        "-f", "--force", action="store_true",
        dest="force", default=False,
        help="force overwrite without asking")
    parser.add_option(
        "--fix-type-names", action="store",
        dest="fixtypenames", default=None,
        help="Fix up (replace) complex type names.")
    parser.add_option(
        "--no-collect-includes", action="store_true",
        dest="no_collect_includes", default=False,
        help="do not process and insert schemas referenced by "
             "xs:include and xs:import elements")
    parser.add_option(
        "--no-redefine-groups", action="store_true",
        dest="no_redefine_groups", default=False,
        help="do not pre-process and redefine xs:group elements")
    (options, args) = parser.parse_args()
    if len(args) == 2:
        inpath = args[0]
        outpath = args[1]
    elif len(args) == 1:
        inpath = args[0]
        outpath = None
    elif len(args) == 0:
        inpath = None
        outpath = None
    else:
        usage(parser)
    prep_schema(inpath, outpath, options)


if __name__ == "__main__":
    #import pdb; pdb.set_trace()
    main()
