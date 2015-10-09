import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')
options.register('outFileName', 'SkimmedEvents.root',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Output file name"
    )
options.register('isData', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Is data?"
    )
options.setDefault('maxEvents', 1000)
options.parseArguments()

process = cms.Process("EvtBuilder")

from infiles_cfi import * 
process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
    files_DY_M50
    ) 
    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

from Analysis.EventSelector.EventBuilder_cff import * 
process.evtbuilder =  EventBuilder.clone()

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string(options.outFileName),
    SelectEvents = cms.untracked.PSet(
      SelectEvents = cms.vstring('p')
      ),
    outputCommands = cms.untracked.vstring(
      "drop *",
      "keep *_*_*_EvtBuilder",
      )
    )

process.p = cms.Path(
    process.evtbuilder
    )

process.outpath = cms.EndPath(process.out)
