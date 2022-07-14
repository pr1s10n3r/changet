project('changet', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

libcurldep = dependency('libcurl', version : '>=7.74.0')
jsoncdep = dependency('json-c', version : '>=0.15')

executable('changet',
           'main.c',
           'board.c',
           'thread.c',
           'list.c',
           install : true,
           dependencies : [libcurldep, jsoncdep])
