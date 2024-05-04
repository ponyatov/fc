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

expr.Int 123, expr.Prim("+", Int(2), Int(3))
