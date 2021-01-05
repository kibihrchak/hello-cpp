def test_cannot_instantiate_class():
    ERROR_NO_CONSTRUCTOR = (r"ruleOfZeroCf.cpp", "19", "14", r"use of deleted function ‘{anonymous}::bar::bar(const {anonymous}::bar&)’")

    import os

    project_abspath = os.path.dirname(os.path.abspath(__file__))
    build_dir_base = os.environ['BUILD_DIR_BASE']

    error_log_file = os.path.join(project_abspath, build_dir_base, 'stderr.log')

    assert os.path.isfile(error_log_file)

    import re
    error_regex = re.compile(r'^' + project_abspath + r'/(.+):(\d+):(\d+): error: (.+)')

    errors = list()
    
    for line in open(error_log_file):
        match = re.match(error_regex, line)
        if match:
            errors.append(match.groups())

    assert ERROR_NO_CONSTRUCTOR in errors
