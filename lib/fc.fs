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
    | Prim of string * expr * expr

printfn "%A" (Int 123, Prim("+", Int 2, Int 3))
