def py_parser_gen(name, grammar_file, visibility=None, **kwargs):
    """Create a miniature of the src image.

    The generated file is prefixed with 'small_'.
    """
    grammar_path = grammar_file.split('/')[0]
    grammar_name = (grammar_file.split('/')[-1]).split('.')[0]
    generated_file_suffixes = [
        "Lexer.py",
        "Parser.py",
        "Listener.py",
        # "Lexer.tokens",
        # ".tokens",
        # "Lexer.interp",
        # ".interp",
    ]

    tool_cmd = "java -Xmx500M -cp $(location @antlr4_complete_jar//file) org.antlr.v4.Tool"
    outs = [
        "{}/{}{}".format(grammar_path, grammar_name, suffix)
        for suffix in generated_file_suffixes
    ]
    copy_commands = '\n'.join(["cp {} $(location {})".format(out, out) for out in outs])
    native.genrule(
        name = name,
        srcs = [grammar_file],
        outs = outs,
        tools = ["@antlr4_complete_jar//file"],
        cmd = """
            {} -Dlanguage=Python3 $<
            {}
        """.format(tool_cmd, copy_commands),
        visibility = visibility,
        **kwargs
    )

