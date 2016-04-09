/*
 * Created by Ojas Mhetar on 2016.04.09  * 
 * Copyright © 2016 Ojas Mhetar. All rights reserved. * 
 */
package com.guardian.entitypackage.service;

import java.util.Set;
import javax.ws.rs.core.Application;

/**
 *
 * @author ojmhetar
 */
@javax.ws.rs.ApplicationPath("webresources")
public class ApplicationConfig extends Application {

    @Override
    public Set<Class<?>> getClasses() {
        Set<Class<?>> resources = new java.util.HashSet<>();
        addRestResourceClasses(resources);
        return resources;
    }

    /**
     * Do not modify addRestResourceClasses() method.
     * It is automatically populated with
     * all resources defined in the project.
     * If required, comment out calling this method in getClasses().
     */
    private void addRestResourceClasses(Set<Class<?>> resources) {
        resources.add(com.guardian.entitypackage.service.EventFacadeREST.class);
        resources.add(com.guardian.entitypackage.service.UserFacadeREST.class);
    }
    
}
