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

type expr =
    | Int of int
    | Op of string * expr * expr

printfn "%A" (Int 123, Op("+", Int 2, Int 3))
