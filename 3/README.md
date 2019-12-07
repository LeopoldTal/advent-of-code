# [Day 3: "Crossed Wires"](https://adventofcode.com/2019/day/3)

## Language

[R](https://www.r-project.org/) is a language for statistics and data analysis.

You can use the R REPL, or the [RStudio](https://rstudio.com/) IDE.

## Puzzle A

I draw each wire on a 2D square matrix. To keep track of intersections and make the pictures nicer, the numbers of the wire are treated as bitwise masks.

This is horribly slow.

[Try it online!](https://tio.run/##jVZtb9MwEP6c/AqraCIdnmg7BmilfBrfhpAmJj6UKkqbtLVInclx6QLst4/z@SV2sg6qSnXu9bnz3ZOKx8dllYk8rdmvImV8JciHM3IxGk3jeFNIFCvJes9XklU8Qesh@R1HOduZp/l4MY0fjMeO5XcV4/KIlw1qRSevT8iEvCJjHaHYLdlmU3Dfm3juFk8nzDSOeHFwaPH3FcQ9JZ3qwDCOMIVIUaXMd5kU7D4hI0q4qA5kRmwwEKyq0hOQIUYoizUW2O0d1hEJttkeUavzNEQwV8Eu0Ye2x4Xz70HWncpFdkgPTBRpXeg2BS0DF2VL4whtmDrVMhMyvadEHxqqLlFobxDqQ1oWfCO3Mbb7Bfmc/Sg0DgIYSMGr/WZL1pVQLbE@z93LYcvKQuExNjOT/V51I0wZRX9IaNQcMTIRzjpK5TjyLJqjFlhd5CbAjl0L2zYLx8kB7k9TZDM5u@aI3dEOPagLLnjeTVYfmFxtk/aKIIr/GdwOYDJhaAdX@tDVXyvxWdgAsL5R4lCqYCgEnTL@D0EvwdVTeZ8EN7JwRgqBXgfTgEvsCDVg8KnRS8Hk4YtI7PU9a6@ymvk3i8tqqTtPiXbAn2bYWaon@IcSu0mE8VqKPSprnCRfAK7wUN@VTCa@HEqlg@EcyHKBUHyi9ImzHQxvBK3SSZuOFAhwmXrplFpxkaxkVqYdfETfSQBPJVRr7Quh0H6t0Z1QKGv8WSeDb6pdJ7kjEDi/PskHXrtCZJT0MQ1x5foVdCSaXqHWlrdwYPdLsEmCHGP46j3u7L@abyErljzlNVGEv80C6VCDg68o6n2J99UjXzWOjnHdzMFgt@zbUoqjQE/aOGmD0rbAGQn3r1PQrE@QiNdxm0Zt584fKquZ@JrG15yjBgnKvnrMkmRlGe6IKlQPyDPv1XP3Qj03b1Izcnlxr4ZtfGkmU0fT82abCREnp6fG@Mxcr0vmrqS3rRhrjm6LYb@cNWjSlajqmvHN0b3Xpf17Z@MIOoM4agM4qIjorbTp0AbekECyupDZjDh/Sr7e3H4ybRLVLvhrlS3rpI3SUoEyz4HkMr7SCALPOR0vYIs6soklJJ4413kb5CMZqb5Bq@qq/Bn@HWT8bi@xNa5kj/xAR8nL7/ylo73wuqBU0xcPNcb37yS8BrDUBKRTu0fr7odC0GiXSsZxsgc37@ntBb2@oFfn8e07evOWXr2h128GU11d0poPp4@PfwE)
