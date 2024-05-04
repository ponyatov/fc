module fc

let about = printfn "F# compiler library"

open System

Environment.SetEnvironmentVariable(
    "PATH",
    Environment.CurrentDirectory + ":" + Environment.GetEnvironmentVariable("PATH")
)

type Token =
    | Int of int
    | Str of string
